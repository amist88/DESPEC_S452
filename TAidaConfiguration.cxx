#include "TAidaConfiguration.h"

#include <algorithm>
#include <fstream>
#include <ios>
#include <iostream>
#include <locale>
#include <limits>
#include <sstream>
#include <string>

TAidaConfiguration* TAidaConfiguration::instance = nullptr;

TAidaConfiguration::TAidaConfiguration(std::string path)
{
  ReadConfiguration(path);
  DSSDtoFEE();
}

inline DSSDSide ParseSide(std::string arg)
{
  std::transform(arg.begin(), arg.end(), arg.begin(), ::tolower);
  if (arg == "junction") return DSSDSide::Junction;
  return DSSDSide::Ohmic;
}

void TAidaConfiguration::ReadConfiguration(std::string path)
{
  fbwindow = std::numeric_limits<double>::max();
  fbenergyh = std::numeric_limits<double>::max();
  fbenergyl = std::numeric_limits<double>::max();

  std::ifstream cfg(path);
  constexpr auto ignore = std::numeric_limits<std::streamsize>::max();
  int sub_DSSD = -1;
  bool sub_Scaler = false;
  while (cfg)
  {
    if (cfg.peek() == '#')
    {
      cfg.ignore(ignore, '\n');
      continue;
    }

    std::string line_s;
    std::getline(cfg, line_s);
    std::istringstream line(line_s);

    bool sub = false;
    if (line.peek() == '-')
    {
      sub = true;
      line.get();
    }

    std::string option;
    std::getline(line, option, ':');
    line.get();

    std::transform(option.begin(), option.end(), option.begin(), ::tolower);
    option.erase(option.find_last_not_of(" \n\r\t") + 1);
    option.erase(0, option.find_first_not_of(" \n\r\t"));

    if (option == "fees")
    {
      line >> fees;
      fee.resize(fees);
      for (FEEConfiguration& f: fee)
      {
        f.DSSD = -1;
      }
    }
    else if (option == "dssds")
    {
      line >> dssds;
      dssd.resize(dssds);
      for (DSSDConfiguration& d : dssd)
      {
        d.DSSD = -1;
      }
    }
    else if (option == "ignorembsts")
    {
      line >> std::boolalpha >> ignorembsts;
    }
    else if (option == "ucesb")
    {
      line >> std::boolalpha >> useucesb;
    }
    else if (option == "stats")
    {
      line >> std::boolalpha >> stats;
    }
    else if (option == "ucesbshift")
    {
      line >> ucesbshift;
    }
    else if (option == "eventwindow")
    {
      line >> eventwindow;
    }
    else if (option == "frontbackwindow")
    {
      line >> fbwindow;
    }
    else if (option == "frontbackenergyh")
    {
      line >> fbenergyh;
    }
    else if (option == "frontbackenergyl")
    {
      line >> fbenergyl;
    }
    else if (option == "dssd")
    {
      line >> sub_DSSD;
      dssd[sub_DSSD - 1].DSSD = sub_DSSD;
    }
    else if (option == "top" && sub && sub_DSSD > 0)
    {
      line >> dssd[sub_DSSD - 1].Top;
    }
    else if (option == "bottom" && sub && sub_DSSD > 0)
    {
      line >> dssd[sub_DSSD - 1].Bottom;
    }
    else if (option == "left" && sub && sub_DSSD > 0)
    {
      line >> dssd[sub_DSSD - 1].Left;
    }
    else if (option == "right" && sub && sub_DSSD > 0)
    {
      line >> dssd[sub_DSSD - 1].Right;
    }
    else if (option == "x" && sub && sub_DSSD > 0)
    {
      std::string arg;
      line >> arg;
      dssd[sub_DSSD - 1].XSide = ParseSide(arg);
    }
    else if (option == "y" && sub && sub_DSSD > 0)
    {
      std::string arg;
      line >> arg;
      dssd[sub_DSSD - 1].YSide = ParseSide(arg);
    }
    else if (option == "scalers")
    {
      sub_Scaler = true;
    }
    else if (sub && sub_Scaler)
    {
      std::string arg;
      std::getline(line, arg);
      int idx = std::strtol(option.c_str(), NULL, 0);
      scalers[idx] = arg;
    }
  }

  if (useucesb && ignorembsts)
  {
    std::cout << "AIDA Configuration Warning: Not ignoring MBS timestamps when ucesb is used" << std::endl;
    ignorembsts = false;
  }

  std::cout << "/////////////////////////////////////////////////////" << std::endl;
  std::cout << "AIDA Configuration: " << fees << " FEEs, " << dssds << " DSSDs, "
    << scalers.size() << " Scalers" << std::endl;

  std::cout << "AIDA Options: ";
  if (ignorembsts) std::cout << "NoMBS ";
  else std::cout << "MBS ";
  if (useucesb) std::cout << "ucesb ";
  if (stats) std::cout << "stats ";
  std::cout << std::endl;
  if (useucesb && ucesbshift) std::cout << "ucesb Timestamps are shifted by " << ucesbshift << " ns" << std::endl;

  std::cout << "AIDA Windows: Event: " << eventwindow << " ns, Front/Back: " << fbwindow << " ns" << std::endl;
  std::cout << "AIDA Gates: Front/Back High: " << fbenergyh << " MeV, Low: " << fbenergyl << " keV" << std::endl;
  std::cout << "/////////////////////////////////////////////////////" << std::endl;
}

void TAidaConfiguration::DSSDtoFEE()
{
  for (DSSDConfiguration& d : dssd)
  {
    fee[d.Top-1].DSSD = d.DSSD;
    fee[d.Top-1].High = true;
    fee[d.Top-1].Side = d.YSide;

    fee[d.Right-1].DSSD = d.DSSD;
    fee[d.Right-1].High = true;
    fee[d.Right-1].Side = d.XSide;

    fee[d.Bottom-1].DSSD = d.DSSD;
    fee[d.Bottom-1].High = false;
    fee[d.Bottom-1].Side = d.YSide;

    fee[d.Left-1].DSSD = d.DSSD;
    fee[d.Left-1].High = false;
    fee[d.Left-1].Side = d.XSide;
  }
}
