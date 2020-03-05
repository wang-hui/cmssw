// -*- C++ -*-
//
// Package:    HCALTest/HCALTestAna
// Class:      HCALTestAna
//
/**\class HCALTestAna HCALTestAna.cc HCALTest/HCALTestAna/plugins/HCALTestAna.cc

Description: [one line class summary]

Implementation:
[Notes on implementation]
*/

// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"

//calo headers
#include "SimDataFormats/CaloHit/interface/PCaloHit.h"
#include "SimDataFormats/CaloHit/interface/PCaloHitContainer.h"
#include "DataFormats/HcalDetId/interface/HcalDetId.h"

//STL headers
#include <vector>
#include <string>
#include <iostream>
//
// class declaration
//

// If the analyzer does not use TFileService, please remove
// the template argument to the base class so the class inherits
// from  edm::one::EDAnalyzer<>
// This will improve performance in multithreaded jobs.

class HCALTestAna : public edm::one::EDAnalyzer<edm::one::SharedResources>  {
	public:
		explicit HCALTestAna(const edm::ParameterSet&);
		~HCALTestAna();

		static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


	private:
		virtual void beginJob() override;
		virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
		virtual void endJob() override;

		edm::EDGetTokenT<std::vector<PCaloHit>> hcalhitsToken_;

};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
HCALTestAna::HCALTestAna(const edm::ParameterSet& iConfig)
{
	//now do what ever initialization is needed
	hcalhitsToken_ = consumes<std::vector<PCaloHit>>(edm::InputTag("g4SimHits","HcalHits","SIM"));
}


HCALTestAna::~HCALTestAna()
{

	// do anything here that needs to be done at desctruction time
	// (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
HCALTestAna::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
	using namespace edm;

	Handle<std::vector<PCaloHit>> hcalhitsHandle;
	iEvent.getByToken(hcalhitsToken_, hcalhitsHandle);
	//   iEvent.getByLabel("g4SimHits", "HcalHits", hand);
	const std::vector<PCaloHit> * SimHits = hcalhitsHandle.product();

	for(auto iter : *SimHits)
	{
		HcalDetId hid(iter.id());
		auto ieta = hid.ieta();
		auto iphi = hid.iphi();
		auto subdet = hid.subdet();
		//std::cout << ieta << ", " << iphi << ", " << subdet << std::endl;
		if(abs(ieta)>39) std::cout << ieta << ", " << iphi << ", " << subdet << std::endl;
	}

}


// ------------ method called once each job just before starting event loop  ------------
void
HCALTestAna::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void
HCALTestAna::endJob()
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
HCALTestAna::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
	//The following says we do not know what parameters are allowed so do no validation
	// Please change this to state exactly what you do use, even if it is no parameters
	edm::ParameterSetDescription desc;
	desc.setUnknown();
	descriptions.addDefault(desc);

	//Specify that only 'tracks' is allowed
	//To use, remove the default given above and uncomment below
	//ParameterSetDescription desc;
	//desc.addUntracked<edm::InputTag>("tracks","ctfWithMaterialTracks");
	//descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(HCALTestAna);
