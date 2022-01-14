
#include "DataManager.C"
// #include "SpacePointConverter.C"

#include <boost/range/adaptor/reversed.hpp>
#include <unistd.h>

bool cmp(const o2::trd::Digit a, const o2::trd::Digit b)
{
  return (a.getDetector()==b.getDetector() && a.getPadRow()==b.getPadRow());
}

list<DataManager::DigitRange> subranges(DataManager::DigitRange rng)
{
  list<DataManager::DigitRange> ranges;

  DataManager::DigitRange r;
  r.b = rng.b;
  r.e = rng.b;

  while ( r.e != rng.e ) {

    if ( !cmp(*r.b,*r.e) ) {
      ranges.push_back(r);
      r.b = r.e;
    }

    r.e++;
  }

  ranges.push_back(r);
  return ranges;
}


void plot()
{

  // ----------------------------------------------------------------------
  // instantiate the class that handles all the data access
  // auto dman = DataManager("./");
  auto dman = DataManager("data/504419/");
  //auto dman = DataManager("/alice/share/simdata/");

  // ----------------------------------------------------------------------
  // create output objects
  // TH2F* padrow = new TH2F("padrow", "padrow",144,0.,144.,30,0.,30.);
  // TCanvas* cnv = new TCanvas("cnv_padrow", "cnv_padrow", 800,600);

  TH1D* hADC = new TH1D("hADC", "ADC spectrum", 1024, -0.5, 1023.5);

  TFile* outfile=new TFile("outfile.root", "RECREATE");

  // SpacePointConverter conv;

  // ----------------------------------------------------------------------
  // loop over time frames and events
  while ( dman.NextTimeFrame() ) {
    while ( dman.NextEvent() ) {

      cout << "EVENT" << endl;

      for (auto& dig : dman.Digits()) {

        if (dig.getDetector()==13 && dig.getROB()==1 && dig.getMCM()==10) {
          cout << dig << endl;
        }

        for (int i=0; i<30; i++) {
          hADC->Fill(dig.getADC()[i]);
        }


      } // digits loop


      // return;

    } // event/trigger record loop
  } // time frame loop

  hADC->Draw();

    // hdet->Draw("lego");
    // padrow->Draw("colz");

}
