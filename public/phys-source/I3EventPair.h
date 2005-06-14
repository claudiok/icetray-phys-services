#ifndef I3EVENTPAIR_H
#define I3EVENTPAIR_H

/**
 * @brief Dumb struct for holding an I3Event and its I3EventHeader
 */
struct EventPair
{
  I3EventPtr event;
  I3EventHeaderPtr header;

  operator bool()
  {
    if(event && header)
      return true;
    return false;
  }
};

#endif
