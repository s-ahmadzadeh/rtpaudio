// ##########################################################################
// ####                                                                  ####
// ####                      RTP Audio Server Project                    ####
// ####                    ============================                  ####
// ####                                                                  ####
// #### RTCP Receiver Implementation                                     ####
// ####                                                                  ####
// #### Version 1.50  --  August 01, 2001                                ####
// ####                                                                  ####
// ####            Copyright (C) 1999-2001 by Thomas Dreibholz           ####
// #### Contact:                                                         ####
// ####    EMail: dreibh@exp-math.uni-essen.de                           ####
// ####    WWW:   http://www.exp-math.uni-essen.de/~dreibh/rtpaudio      ####
// ####                                                                  ####
// #### ---------------------------------------------------------------- ####
// ####                                                                  ####
// #### This program is free software; you can redistribute it and/or    ####
// #### modify it under the terms of the GNU General Public License      ####
// #### as published by the Free Software Foundation; either version 2   ####
// #### of the License, or (at your option) any later version.           ####
// ####                                                                  ####
// #### This program is distributed in the hope that it will be useful,  ####
// #### but WITHOUT ANY WARRANTY; without even the implied warranty of   ####
// #### MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the    ####
// #### GNU General Public License for more details.                     ####
// ####                                                                  ####
// ##########################################################################


#include "tdsystem.h"
#include "rtcpreceiver.h"
#include "internetflow.h"
#include "tools.h"


// Debug mode: Print corrupted RTCP packets
#define DEBUG


// ###### Constructor #######################################################
RTCPReceiver::RTCPReceiver()
   : Thread("RTCPReceiver")
{
   Server         = NULL;
   ReceiverSocket = NULL;
}


// ###### Constructor #######################################################
RTCPReceiver::RTCPReceiver(RTCPAbstractServer* server, Socket* receiverSocket)
   : Thread("RTCPReceiver")
{
   init(server,receiverSocket);
}


// ###### Initialize ########################################################
void RTCPReceiver::init(RTCPAbstractServer* server, Socket* receiverSocket)
{
   Server         = server;
   ReceiverSocket = receiverSocket;
}


// ###### Destructor ########################################################
RTCPReceiver::~RTCPReceiver()
{
   stop();
}


// ###### Receiver loop #####################################################
void RTCPReceiver::run()
{
   if(ReceiverSocket == NULL) {
      std::cerr << "ERROR: RTCPReceiver::run() - RTCPReceiver is uninitialized!"
                << std::endl;
      return;
   }

   InternetFlow flow;
   for(;;) {
      // ====== Read RTCP packet ============================================
      char packetData[8192];
      integer receivedPacketSize =
         ReceiverSocket->receiveFrom((char*)&packetData,sizeof(packetData),flow,0);
      if(receivedPacketSize < (ssize_t)sizeof(RTCPCommonHeader)) {
         if(receivedPacketSize > 0) {
            std::cerr << "WARNING: RTCPReceiver::run() - Received bad RTCP header" << std::endl;
         }
         continue;
      }


      // ====== Verify RTCP packet ==========================================
      RTCPCommonHeader* header  = (RTCPCommonHeader*)&packetData;
      const cardinal packetSize = header->getLength();
/*
      std::cout << "RTCP Common Header\n";
      std::cout << "   Version     : " << (cardinal)header->getVersion()    << "\n";
      std::cout << "   Padding     : " << (cardinal)header->getPadding()    << "\n";
      std::cout << "   Count       : " << (cardinal)header->getCount()      << "\n";
      std::cout << "   Packet Type : " << (cardinal)header->getPacketType() << "\n";
      std::cout << "   Length      : " << (cardinal)header->getLength()     << std::endl;
*/
      if(receivedPacketSize < (integer)packetSize) {
#ifdef DEBUG
         std::cerr << "RTCP packet: receivedPacketSize < packetSize: "
              << receivedPacketSize << " <=> " << packetSize << std::endl;
#endif
         continue;
      }

      if(header->getVersion() != RTPConstants::RTPVersion) {
#ifdef DEBUG
         std::cerr << "RTCP packet: Invalid RTP version: " << header->getVersion() << std::endl;
#endif
         continue;
      }

      RTCPCommonHeader* r    = (RTCPCommonHeader*)&packetData;
      RTCPCommonHeader* rend = (RTCPCommonHeader*)(long)r + packetSize;
      do {
         r = (RTCPCommonHeader*)((long*)r + (long)r->getLength());
      } while((r < rend) && (r->getVersion() == RTPConstants::RTPVersion));
      if(r != rend) {
#ifdef DEBUG
         std::cerr << "RTCP packet: Length check failed!" << std::endl;
#endif
         continue;
      }


      // ====== Get type and invoke server function =========================
      synchronized();
      switch(header->getPacketType()) {

         // ====== Packet is a Receiver Report ==============================
         case RTCP_RR:
            {
               RTCPReceiverReport* receiverReport = (RTCPReceiverReport*)&packetData;
               cardinal bytes = sizeof(RTCPReceiverReport);
               cardinal layer = 0;
               card32   ssrc  = 0;
               for(cardinal i = 0;i < receiverReport->getCount();i++) {
                  if((bytes + sizeof(RTCPReceptionReportBlock)) <= packetSize) {
                     if(receiverReport->rr[i].getSSRC() == ssrc) {
                        layer++;
                     }
                     else {
                        layer = 0;
                        ssrc  = receiverReport->rr[i].getSSRC();
                     }
                     Server->receivedReceiverReport(
                        flow, receiverReport->getSSRC(),
                        &receiverReport->rr[i], layer);
                  }
                  else {
#ifdef DEBUG
                     std::cerr << "RTCP packet: Invalid receiver report length!" << std::endl;
#endif
                     break;
                  }
                  bytes += sizeof(RTCPReceptionReportBlock);
               }
            }
          break;

         // ====== Packet is a Sender Report ================================
         case RTCP_SR:
            {
               RTCPSenderReport* senderReport = (RTCPSenderReport*)&packetData;
               cardinal bytes = (long)&senderReport->rr[0] - (long)senderReport;
               cardinal layer = 0;
               card32   ssrc  = 0;
               for(cardinal i = 0;i < senderReport->getCount();i++) {
                  if((bytes + sizeof(RTCPReceptionReportBlock)) <= packetSize) {
                     if(senderReport->rr[i].getSSRC() == ssrc) {
                        layer++;
                     }
                     else {
                        layer = 0;
                        ssrc  = senderReport->rr[i].getSSRC();
                     }
                     Server->receivedSenderReport(
                        flow, senderReport->getSSRC(),
                        &senderReport->rr[i], layer);
                  }
                  else {
#ifdef DEBUG
                     std::cerr << "RTCP packet: Invalid sender report length!" << std::endl;
#endif
                     break;
                  }
                  bytes += sizeof(RTCPReceptionReportBlock);
               }
            }
          break;

         // ====== Packet is a Source Description ===========================
         case RTCP_SDES:
            {
               RTCPSourceDescription* sdes          = (RTCPSourceDescription*)&packetData;
               const RTCPSourceDescriptionItem* end = (RTCPSourceDescriptionItem*)((long)sdes + sdes->getLength());
               RTCPSourceDescriptionChunk* sd       = &sdes->Chunk[0];
               RTCPSourceDescriptionItem* rsp;
               RTCPSourceDescriptionItem* rspn;
               integer count = sdes->getCount();
               while(--count >= 0) {
                  rsp = &sd->Item[0];
                  if(rsp >= end) {
                     break;
                  }
                  for ( ;rsp->Type;rsp = rspn) {
                     rspn = (RTCPSourceDescriptionItem*)((char*)rsp + rsp->Length + 2);
                     if(rspn >= end) {
                        rsp = rspn;
                        break;
                     }
                     Server->receivedSourceDescription(
                         flow, sd->SRC, rsp->Type, rsp->Data, rsp->Length);
                  }
                  rsp = (RTCPSourceDescriptionItem*)((long)sd + (((char*)rsp - (char*)sd) >> 2) + 1);
               }
            }
          break;

         // ====== Packet is a Bye message ==================================
         case RTCP_BYE:
            {
               RTCPBye* bye = (RTCPBye*)&packetData;
               for(cardinal i = 0;i < bye->getCount();i++) {
                  Server->receivedBye(flow, bye->getSource(i),
                                      RTCPAbstractServer::DeleteReason_UserBye);
               }
            }
           break;

         // ====== Packet is an App message =================================
         case RTCP_APP:
            {
               RTCPApp* app = (RTCPApp*)&packetData;
               Server->receivedApp(flow,
                                   app->getSource(),
                                   app->getName(),
                                   (void*)app->getData(),
                                   packetSize - sizeof(RTCPCommonHeader) - 8);
            }
           break;

         // ====== Packet type is unknown ===================================
         default:
            receivedPacketSize = 0;
#ifdef DEBUG
            std::cerr << "RTCP packet: Unknown SDES type "
                      << header->getPacketType() << std::endl;
#endif
          break;

      }
      unsynchronized();
      AverageRTCPSize = (1.0/16.0) * receivedPacketSize + (15.0/16.0) * AverageRTCPSize;
   }
}
