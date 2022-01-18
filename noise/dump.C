

void dump()
{

    TTree* o2sim;

    auto mainfile = new TFile("data/504419/trddigits.root");
    mainfile->GetObject("o2sim", o2sim);
    o2sim->AddFriend("o2sim", "data/504419/trdtracklets.root");

    TTreeReader* reader = new TTreeReader(o2sim);

    auto trgrecords = new TTreeReaderArray<o2::trd::TriggerRecord>(*reader, "TrackTrg");
    auto digits     = new TTreeReaderArray<o2::trd::Digit>(*reader, "TRDDigit");
    // auto tracklets  = new TTreeReaderArray<o2::trd::Tracklet>(*reader, "Tracklet");

    while (reader->Next()) {
        cout << "Hello. " << trgrecords->GetSize() << " trigger records" << endl; 

        for (auto rec: trgrecords) {
            cout << rec << endl;
        }

        // for (int iEvent=0; iEvent<trgrecords->GetSize(); iEvent++) {
        //     auto evrec = trgrecords->At(iEvent);
        //     cout << "    " << evrec.getNumberOfDigits() << " digits" 
        //          << "    " << evrec.getNumberOfTracklets() << " tracklets"
        //          << endl; 
        // }

        for (auto dig : *digits) {
            cout << "DIGIT: " << dig << endl;
            // cout << dig.getDetector() << "," 
            //      << dig.getROB() << "," << dig.getMCM() << ","
            //      << dig.getChannel()
            //      << endl;
        }

    }

}