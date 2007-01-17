/*
 *  $Id: extsocketdescriptor.h,v 1.2 2002/08/16 16:24:51 dreibh Exp $
 *
 * SCTP implementation according to RFC 2960.
 * Copyright (C) 1999-2002 by Thomas Dreibholz
 *
 * Realized in co-operation between Siemens AG
 * and University of Essen, Institute of Computer Networking Technology.
 *
 * Acknowledgement
 * This work was partially funded by the Bundesministerium für Bildung und
 * Forschung (BMBF) of the Federal Republic of Germany (Förderkennzeichen 01AK045).
 * The authors alone are responsible for the contents.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * There are two mailinglists available at http://www.sctp.de which should be
 * used for any discussion related to this implementation.
 *
 * Contact: discussion@sctp.de
 *          dreibh@exp-math.uni-essen.de
 *
 * Purpose: Extended Socket Descriptor
 *
 */


#ifndef EXTSOCKETDESCRIPTOR_H
#define EXTSOCKETDESCRIPTOR_H


#include "tdsystem.h"
#include "sctpsocket.h"
#include "sctpassociation.h"



// ###### ExtSocketDescriptor structure #####################################
struct ExtSocketDescriptor
{
   enum ExtSocketDescriptorTypes {
      ESDT_Invalid = 0,
      ESDT_System  = 1,
      ESDT_SCTP    = 2
   };

   unsigned int Type;

   union ExtSocketDescriptorUnion {
      int SystemSocketID;
      struct SCTP {
         int              Domain;
         int              Type;
         SCTPSocket*      SCTPSocketPtr;
         SCTPAssociation* SCTPAssociationPtr;
         int              Parent;
         int              Flags;
         sctp_initmsg     InitMsg;
         linger           Linger;
         bool             ConnectionOriented;
      } SCTPSocketDesc;
   } Socket;
};


// ###### Class for ExtSocketDescriptor management ##########################
class ExtSocketDescriptorMaster
{
   protected:
   ExtSocketDescriptorMaster();

   public:
   ~ExtSocketDescriptorMaster();

   public:
   inline static ExtSocketDescriptor* getSocket(const int id);
   static int setSocket(const ExtSocketDescriptor& newSocket);
   static const unsigned int MaxSockets = FD_SETSIZE;

   private:
   static ExtSocketDescriptorMaster MasterInstance;
   static ExtSocketDescriptor Sockets[MaxSockets];
};


#endif
