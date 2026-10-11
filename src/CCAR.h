#ifndef CCAR_INC_H
#define CCAR_INC_H

#ifdef CCAR_NATURAL
/** Traffic car state extending the natural CBaddy model. */
struct CCar : CBaddy
{
    CCar(short *pInfo, int nodeIndex, int type);
    virtual ~CCar();
    virtual void AI();
    virtual int ExecuteCommand(unsigned short command);

    int mCurrentRoadSegment;
    int mHonkLock;
};
#else
/** Traffic car state extending the shared baddy layout. */
struct CCar : CBaddy
{
    /** Initialize a traffic car from one trigger record. */
    CCar(short *pInfo, int nodeIndex, int type);
    /** Advance the car along its road route. */
    void AI();
    /** Accept one scripted car command. */
    int ExecuteCommand(unsigned short command);

    int mCurrentRoadSegment;
    int mHonkLock;
};
#endif // CCAR_NATURAL

#endif // CCAR_INC_H
