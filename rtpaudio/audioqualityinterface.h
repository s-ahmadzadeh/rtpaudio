// ##########################################################################
// ####                                                                  ####
// ####                      RTP Audio Server Project                    ####
// ####                    ============================                  ####
// ####                                                                  ####
// #### Audio Quality Interface                                          ####
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


#ifndef AUDIOQUALITYINTERFACE_H
#define AUDIOQUALITYINTERFACE_H


#include "tdsystem.h"


namespace Coral {


/**
  * This class is an interface for getting audio quality.
  *
  * @short   Audio Quality Interface
  * @author  Thomas Dreibholz (dreibh@exp-math.uni-essen.de)
  * @version 1.0
  */
class AudioQualityInterface
{
   // ====== Getting values =================================================
   public:
   /**
     * Destructor.
     */
   virtual ~AudioQualityInterface() { };

   /**
     * Get sampling rate.
     *
     * @return Sampling rate.
     */
   virtual card16 getSamplingRate() const = 0;

   /**
     * Get number of bits.
     *
     * @return Number of bits.
     */
   virtual card8 getBits() const = 0;

   /**
     * Get number of channels.
     *
     * @return Number of channels.
     */
   virtual card8 getChannels() const = 0;


   /**
     * Get byte order.
     *
     * @return Byte order: BIG_ENDIAN, LITTLE_ENDIAN.
     */
   virtual card16 getByteOrder() const = 0;


   // ====== Calculating bandwidth settings =================================
   /**
     * Get bytes per second.
     *
     * @return Bytes per second.
     */
   virtual cardinal getBytesPerSecond() const = 0;

   /**
     * Get bits per sample.
     *
     * @return Bits per sample.
     */
   virtual cardinal getBitsPerSample() const = 0;


   // ====== Comparision operators ==========================================
   /**
     * Implementation of == operator.
     */
   inline int operator==(const AudioQualityInterface& quality) const;

   /**
     * Implementation of != operator.
     */
   inline int operator!=(const AudioQualityInterface& quality) const;

   /**
     * Implementation of <= operator.
     * Note: This operator does not compare byte orders!
     */
   inline int operator<=(const AudioQualityInterface& quality) const;

   /**
     * Implementation of < operator.
     * Note: This operator does not compare byte orders!
     */
   inline int operator<(const AudioQualityInterface& quality) const;

   /**
     * Implementation of >= operator.
     * Note: This operator does not compare byte orders!
     */
   inline int operator>=(const AudioQualityInterface& quality) const;

   /**
     * Implementation of > operator.
     * Note: This operator does not compare byte orders!
     */
   inline int operator>(const AudioQualityInterface& quality) const;
};


/**
  * This class is an interface for getting and setting audio quality.
  * It extends AudioQualityInterface with setting functions.
  *
  * @short   Adjustable Audio Quality Interface
  * @author  Thomas Dreibholz (dreibh@exp-math.uni-essen.de)
  * @version 1.0
  */
class AdjustableAudioQualityInterface : virtual public AudioQualityInterface
{
   public:
   /**
     * Set sampling rate.
     *
     * @param samplingRate New sampling rate.
     * @return New sampling rate.
     */
   virtual card16 setSamplingRate(const card16 samplingRate) = 0;

   /**
     * Set number of bits.
     *
     * @param samplingRate New number of bits.
     * @return New number of bits.
     */
   virtual card8 setBits(const card8 bits) = 0;

   /**
     * Set number of channels.
     *
     * @param samplingRate New number of channels.
     * @return New number of channels.
     */
   virtual card8 setChannels(const card8 channels) = 0;


   /**
     * Set byte order.
     *
     * @param byteOrder New byte order: BIG_ENDIAN, LITTLE_ENDIAN.
     * @return New byte order.
     */
   virtual card16 setByteOrder(const card16 byteOrder) = 0;


   /**
     * Set quality from AudioQualityInterface.
     *
     * @param quality AudioQualityInterface.
     */
   inline void setQuality(const AudioQualityInterface& quality);
};


}


#include "audioqualityinterface.icc"


#endif
