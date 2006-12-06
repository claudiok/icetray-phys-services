/**
 * copyright  (C) 2004
 * the icecube collaboration
 * $Id: TWRTWRKey2ChannelID.h 13154 2005-12-01 21:45:55Z tschmidt $
 *
 * @file TWRTWRKey2ChannelID.h
 * @version $Revision: 1.10 $
 * @date $Date: 2005-12-01 16:45:55 -0500 (Thu, 01 Dec 2005) $
 * @author tschmidt
 */
#ifndef TWRTWRKEY2CHANNELID_H_INCLUDED
#define TWRTWRKEY2CHANNELID_H_INCLUDED

// forward declarations


// header files

#include <utility>

#include <icetray/I3DefaultName.h>
#include <icetray/I3FrameObject.h>
#include <icetray/I3Logging.h>
#include <dataclasses/I3Time.h>

// definitions


/**
 * @brief Abstract base class that defines an interface for a service
 * that provides conversions between TWR ID + channel no. and channel ID.
 * 
 * \note
 * In contrast to the static OM key/motherboard ID and OM key/channel ID conversion tables,
 * the channel ID/TWR key conversion table may change in time. Therefore two versions of
 * each access method are provided. A time dependent and a time independent one.
 * Time independent access methods will always access the current conversion table in memory,
 * which can be selected calling Select(const I3Time& time) and for which one can check
 * the validity period (GetValidityPeriod()). Time dependent access methods will not access
 * or select the current conversion table - they will individually access a conversion
 * table that is addressed by the time given.
 */
class TWRTWRKey2ChannelID
{
 public:
  /** Identifies the data of a given TWR within the TWR binary output files.
   * 
   * This was just a running index in the past and will be the TWR ID in future (2007 et sqq.).
   * The running index was determined by the configuration sequence.
   * In contrast, the TWR ID is part of the configuration.
   * As yet, the TWR ID is composed by the crate no. (multiplied by 0x10)
   * and (plus) the TWR no..
   */
  typedef unsigned int TWRID;
  /** The TWR key is a pair of a TWR ID and a channel no..
   */
  typedef std::pair<TWRID, unsigned int> TWRKey;


  /** Default constructor.
   */
  TWRTWRKey2ChannelID();
  /** Destructor.
   */
  virtual ~TWRTWRKey2ChannelID() = 0;
  /** Checks whether a specified TWR ID + channel no. exists in the conversion table.
   * 
   * @param twrID The TWR ID.
   * @param channel The channel no.
   * @return True, if it exists in the table.
   */
  virtual bool TWRKeyExists(unsigned int twrID, unsigned int channel) const = 0;
  /** Checks whether a specified TWR ID + channel no. exists in the conversion table.
   * 
   * @param twrID The TWR ID.
   * @param channel The channel no.
   * @param time Time the check should be issued for.
   * @return True, if it exists in the table.
   */
  virtual bool TWRKeyExists(unsigned int twrID, unsigned int channel,
                            const I3Time& tm) const = 0;
  /** Checks whether a specified TWR ID + channel no. exists in the conversion table.
   * 
   * @param key The TWR ID + channel no..
   * @return True, if it exists in the table.
   */
  virtual bool TWRKeyExists(TWRKey key) const = 0;
  /** Checks whether a specified TWR ID + channel no. exists in the conversion table.
   * 
   * @param key The TWR ID + channel no..
   * @param tm Time the check should be issued for.
   * @return True, if it exists in the table.
   */
  virtual bool TWRKeyExists(TWRKey key, const I3Time& tm) const = 0;
  /** Returns the channel ID associated with a specified TWR ID + channel no..
   * 
   * @param twrID The TWR ID.
   * @param channel The channel no..
   * @return The channel ID.
   */
  virtual unsigned int GetChannelID(unsigned int twrID, unsigned int channel) const = 0;
  /** Returns the channel ID associated with a specified TWR ID + channel no..
   * 
   * @param twrID The TWR ID.
   * @param channel The channel no..
   * @param tm Time the channel ID should be issued for.
   * @return The channel ID.
   */
  virtual unsigned int GetChannelID(unsigned int twrID, unsigned int channel,
                                    const I3Time& tm) const = 0;
  /** Returns the channel ID associated with a specified TWR ID + channel no..
   * 
   * @param key The TWR ID + channel no..
   * @return The channel ID.
   */
  virtual unsigned int GetChannelID(TWRKey key) const = 0;
  /** Returns the channel ID associated with a specified TWR ID + channel no..
   * 
   * @param key The TWR ID + channel no..
   * @param tm Time the channel ID should be issued for.
   * @return The channel ID.
   */
  virtual unsigned int GetChannelID(TWRKey key, const I3Time& tm) const = 0;
  /** Checks whether a specified channel ID exists in the conversion table.
   * 
   * @param channelID The channel ID.
   * @return True, if it exists in the table.
   */
  virtual bool ChannelIDExists(unsigned int channelID) const = 0;  
  /** Checks whether a specified channel ID exists in the conversion table.
   * 
   * @param channelID The channel ID.
   * @param tm Time the check should be issued for.
   * @return True, if it exists in the table.
   */
  virtual bool ChannelIDExists(unsigned int channelID, const I3Time& tm) const = 0;  
  /** Returns the TWR ID + channel no. associated with a specified channel ID.
   * 
   * @param channelID The channel ID.
   * @return The TWR ID + channel no..
   */
  virtual TWRKey GetTWRKey(unsigned int channelID) const = 0;
  /** Returns the TWR ID + channel no. associated with a specified channel ID.
   * 
   * @param channelID The channel ID.
   * @param tm Time the TWR ID + channel no. should be issued for.
   * @return The TWR ID + channel no..
   */
  virtual TWRKey GetTWRKey(unsigned int channelID, const I3Time& tm) const = 0;
  /** Returns the validity period of the current conversion table.
   * 
   * @return Start and end time ([start, end[) of the validity period.
   */
  virtual const std::pair<I3Time, I3Time>& GetValidityPeriod() const = 0;
  /** Select the current conversion table.
   * 
   * @param tm Time the conversion table should be issued for.
   */
  virtual void Select(const I3Time& tm) = 0;

  private:
  // private copy constructors and assignment
  TWRTWRKey2ChannelID(const TWRTWRKey2ChannelID&);
  TWRTWRKey2ChannelID& operator=(const TWRTWRKey2ChannelID&);


  // logging
  SET_LOGGER("TWRTWRKey2ChannelID");
};

/**
 * pointer type to insulate users from memory management
 */
I3_POINTER_TYPEDEFS(TWRTWRKey2ChannelID);

/**
 * define a default name to address service in a context
 */
I3_DEFAULT_NAME(TWRTWRKey2ChannelID);

#endif /*TWRTWRKEY2CHANNELID_H_INCLUDED*/
