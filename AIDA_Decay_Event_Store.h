#ifndef TAIDAEVENT_H
#define TAIDAEVENT_H

#include "TGo4EventElement.h"

#define AIDA_EVENT_ADC 3
#define AIDA_EVENT_INFO 2

// AidaEvent: An Unpacker AIDA ADC single event
class AidaEvent : public TObject
{
public:
  int ID;

  /* Raw ADC Data */
  bool HighEnergy;
  int Module;
  int ADC;
  int Channel;
  int Data;
  int64_t Time;
  int64_t FastTime; // time of last fast discriminator  for this channel

  /* Mapped to DSSD */
  int DSSD;
  int Side;
  int Strip;
  int Intensity; /* ADC Data corrected for polarity */
  double Energy;



  AidaEvent();

  void Zero();
  virtual ~AidaEvent() {}

  ClassDef(AidaEvent, 1)
};

// AidaCluster: Used to collect adjacent strips for charge splitting
// Not saved in tree but
class AidaCluster
{
public:
  int DSSD;
  int Side;
  bool HighEnergy;
  double Energy;
  double Strip;
  int64_t Time;
  int64_t FastTime;
  int N;

  // DSSD > Side > Strip (Time?)
  AidaCluster() { Zero() ; }
  void Zero();
  ~AidaCluster() {}
  void AddEvent(AidaEvent const& event);
  void AddCluster(AidaCluster const& cluster);
  bool IsAdjacent(AidaEvent const& event) const;
  bool IsGoodTime(AidaEvent const& event, int window = 2000) const;
  bool IsGoodTime(AidaCluster const& event, int window) const;

  int StripMin;
  int StripMax;
  int64_t TimeMin;
  int64_t TimeMax;
  int64_t FastTimeMin;
  int64_t FastTimeMax;
  int StripSum;
};

// AidaHit: Physical detector hits: front-back matched
class AidaHit : public TObject
{
public:
  int Event;

  int DSSD;
  // Coordinate in Strip & Position
  double StripX;
  double StripY;
  double PosX;
  double PosY;

  double Energy;
  double EnergyFront;
  double EnergyBack;

  // Cluster Size for correlations
  int StripXMin;
  int StripXMax;
  int StripYMin;
  int StripYMax;
  int ClusterSizeX;
  int ClusterSizeY;

  int64_t Time;
  int64_t TimeFront;
  int64_t TimeBack;
  int64_t FastTime;
  int64_t FastTimeFront;
  int64_t FastTimeBack;

  // If the implant is believed to have stopped here (AIDA only veto)
  bool Stopped;

  AidaHit() { Zero(); }
  void Zero();
  virtual ~AidaHit() {}

  ClassDef(AidaHit, 3)
};

class AidaScaler : public TObject
{
public:
  int Module;
  int64_t Value;
  int64_t Time;

  AidaScaler() {}
  AidaScaler(int m, int64_t v, int64_t t) : Module(m), Value(v), Time(t) {}

  ClassDefNV(AidaScaler, 2);
};

#endif /* TAIDAEVENT_H */
