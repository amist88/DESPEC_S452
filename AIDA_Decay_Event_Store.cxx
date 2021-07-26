#include "AIDA_Decay_Event_Store.h"
#include <iostream>

AidaEvent::AidaEvent()
{
  Zero();
}

void AidaEvent::Zero() {
  ID = 0;
  HighEnergy = false;
  Module = 0;
  ADC = 0;
  Channel = 0;
  Data = 0;
  Time = 0;
  DSSD = 0;
  Side = 0;
  Strip = 0;
  Intensity = 0;
  Energy = 0;
  FastTime = 0;
}

void AidaHit::Zero() {
  Event = 0;
  DSSD = 0;
  StripX = 0;
  StripY = 0;
  PosX = 0;
  PosY = 0;

  Energy = 0;
  EnergyFront = 0;
  EnergyBack = 0;
  Time = 0;
  TimeFront = 0;
  TimeBack = 0;
  Stopped = false;
}

void AidaCluster::Zero()
{
  DSSD = -1;
  Side = 0;
  HighEnergy = false;
  Energy = 0;
  Strip = 0;
  Time = 0;
  FastTime = 0;
  StripMin = 0;
  StripMax = 0;
  TimeMin = 0;
  TimeMax = 0;
  FastTimeMin = 0;
  FastTimeMax = 0;
  StripSum = 0;
  N = 0;
}

void AidaCluster::AddEvent(AidaEvent const& event)
{
  if (DSSD == -1)
  {
    DSSD = event.DSSD;
    Side = event.Side;
    HighEnergy = event.HighEnergy;
    StripMin = event.Strip;
    StripMax = event.Strip;
    TimeMin = event.Time;
    TimeMax = event.Time;
    FastTimeMin = event.FastTime;
    FastTimeMax = event.FastTime;
  }
  Energy += event.Energy;
  if(event.Strip < StripMin) StripMin = event.Strip;
  if(event.Strip > StripMax) StripMax = event.Strip;
  if(event.Time < TimeMin) TimeMin = event.Time;
  if(event.Time > TimeMax) TimeMax = event.Time;
  if(event.FastTime < FastTimeMin) FastTimeMin = event.FastTime;
  if(event.FastTime > FastTimeMax) FastTimeMax = event.FastTime;
  StripSum += event.Strip;
  Strip = (double)StripSum / ++N;
  Time = TimeMin;
  FastTime = FastTimeMin;
}

void AidaCluster::AddCluster(AidaCluster const& cluster)
{
  if (DSSD == -1)
  {
    *this = cluster;
    return;
  }

  if (cluster.StripMin < StripMin) StripMin = cluster.StripMin;
  if (cluster.StripMax > StripMax) StripMax = cluster.StripMax;
  if (cluster.TimeMin < TimeMin) TimeMin = cluster.TimeMin;
  if (cluster.TimeMax > TimeMax) TimeMax = cluster.TimeMax;
  if (cluster.FastTimeMin < FastTimeMin) FastTimeMin = cluster.FastTimeMin;
  if (cluster.FastTimeMax > FastTimeMax) FastTimeMax = cluster.FastTimeMax;
  Energy += cluster.Energy;
  StripSum += cluster.StripSum;
  N += cluster.N;
  Strip = (double)StripSum / N;
  Time = TimeMin;
  FastTime = FastTimeMin;
}

bool AidaCluster::IsAdjacent(AidaEvent const& event) const
{
  if (DSSD == -1) return true;
  if (event.DSSD != DSSD || event.Side != Side) return false;
  if (event.Strip >= StripMin - 1 && event.Strip <= StripMax + 1) return true;
  return false;
}

bool AidaCluster::IsGoodTime(AidaEvent const& event, int window) const
{
  if (DSSD == -1) return true;

  if (event.Time >= TimeMin - window && event.Time <= TimeMax + window) return true;
  return false;
}

bool AidaCluster::IsGoodTime(AidaCluster const& event, int window) const
{
  if (DSSD == -1) return true;

  if (event.TimeMin >= TimeMin - window && event.TimeMin <= TimeMax + window) return true;
  if (event.TimeMax >= TimeMin - window && event.TimeMax <= TimeMax + window) return true;
  return false;
}
