/*
 *  $Id: breakdetector.cc,v 1.2 2002/08/16 16:24:51 dreibh Exp $
 *
 * SCTP implementation according to RFC 2960.
 * Copyright (C) 1999-2001 by Thomas Dreibholz
 *
 * Realized in co-operation between Siemens AG
 * and University of Essen, Institute of Computer Networking Technology.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 * There are two mailinglists available at www.sctp.de which should be used for
 * any discussion related to this implementation.
 *
 * Contact: discussion@sctp.de
 *          dreibh@exp-math.uni-essen.de
 *
 * Purpose:    Break Detector
 *
 */

#include "tdsystem.h"
#include "breakdetector.h"
#include "tools.h"


#include <signal.h>



// Kill after timeout: Send kill signal, if Ctrl-C is pressed again
// after more than KILL_TIMEOUT microseconds,
#define KILL_AFTER_TIMEOUT
#define KILL_TIMEOUT 2000000



// ###### Global variables ##################################################
static bool   DetectedBreak = false;
static bool   PrintedBreak  = false;
static bool   Quiet         = false;
static pid_t  MainThreadPID = getpid();
#ifdef KILL_AFTER_TIMEOUT
static bool   PrintedKill   = false;
static card64 LastDetection = (card64)-1;
#endif


// ###### Handler for SIGINT ################################################
void breakDetector(int signum)
{
   DetectedBreak = true;

#ifdef KILL_AFTER_TIMEOUT
   if(!PrintedKill) {
      const card64 now = getMicroTime();
      if(LastDetection == (card64)-1) {
         LastDetection = now;
      }
      else if(now - LastDetection >= 2000000) {
         PrintedKill = true;
         cerr << endl << "*** Kill ***" << endl << endl;
         kill(MainThreadPID,SIGKILL);
      }
   }
#endif
}


// ###### Install break detector ############################################
void installBreakDetector()
{
   DetectedBreak = false;
   PrintedBreak  = false;
   Quiet         = false;
#ifdef KILL_AFTER_TIMEOUT
   PrintedKill   = false;
   LastDetection = (card64)-1;
#endif
   signal(SIGINT,&breakDetector);
}


// ###### Unnstall break detector ###########################################
void uninstallBreakDetector()
{
   signal(SIGINT,SIG_DFL);
#ifdef KILL_AFTER_TIMEOUT
   PrintedKill   = false;
   LastDetection = (card64)-1;
#endif
   DetectedBreak = false;
   PrintedBreak  = false;
   Quiet         = false;
}


// ###### Check, if break has been detected #################################
bool breakDetected()
{
   if((DetectedBreak) && (!PrintedBreak)) {
      if(!Quiet) {
         cerr << endl << "*** Break ***    Signal #" << SIGINT << endl << endl;
      }
      PrintedBreak = getMicroTime();
   }
   return(DetectedBreak);
}


// ###### Send break to main thread #########################################
void sendBreak(const bool quiet)
{
   Quiet = quiet;
   kill(MainThreadPID,SIGINT);
}
