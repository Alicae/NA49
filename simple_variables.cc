#include "simple_variables.h"
using namespace std;

Int_t simple_variables(char* productionTag, int maxFileNumber = 10000)
{
  TStopwatch timer;
  timer.Reset();
  timer.Start();

  char runType[100];
  if ( strcmp(productionTag, "01D")==0 )
    sprintf(runType, "1/4std--40GeV-minbias-01D");
  else if ( strcmp(productionTag, "02C")==0 )
    sprintf(runType, "1/4std+-40GeV-minbias-02C");
  else
    {
    cout << "There is no such production tag as " << productionTag << endl;
    cout << "Available production tags are: 01D 02C" << endl;
    return 0;
     }

  char inputFileList[200];
  sprintf(inputFileList, "/afs/cern.ch/work/a/alzaytse/public/na49/data/%s/full.list", productionTag);

  TFile* outputFile1 = new TFile("./output1.root","RECREATE");
  TTree* myTree  = new TTree("data","data");
  TH1F* hPhi = new TH1F("hPhi", "phi", 260,-0.1,6.4);
  TH1F* hPt = new TH1F("hPt", "p_{T}", 240,0,3);
  TH1F* hEta = new TH1F("hEta", "pseudorapidity", 200,0,8);
  TH2F* hpt_vs_eta = new TH2F("hpt_vs_eta","pt_vs_eta",240,0,3,240,0,8);
  TH2F* hphi_vs_eta = new TH2F("hphi_vs_eta","phi_vs_eta",240,0,8,260,-0.1,6.4);
  TH1F* hEveto = new TH1F("hEveto", "veto calorimeter energy", 100,200,10000);
  TH1F* hVertexX = new TH1F("hVertexX", "VertexX", 60,-0.3,0.3);
  TH1F* hVertexX1 = new TH1F("hVertexX1", "VertexX1", 60,-0.3,0.3);
  TH1F* hVertexX2 = new TH1F("hVertexX2", "VertexX2", 60,-0.3,0.3);

  TH1F* hVertexY = new TH1F("hVertexY", "VertexY", 60,-1,1);
  TH1F* hVertexY1 = new TH1F("hVertexY1", "VertexY1", 60,-1,1);
  TH1F* hVertexY2 = new TH1F("hVertexY2", "VertexY2", 60,-1,1);
  TH2F* hVertexXY = new TH2F("hVertexXY", "VertexXY",60,-0.3,0.3, 60,-1,1);
  TH1F* hVertexZ = new TH1F("hVertexZ", "VertexZ", 50,-605,-560);
  TH1F* hPz = new TH1F("hPz", "Pz", 240,0,20);
  TH1F* hSigPx = new TH1F("hSigPx", "SigPx", 240,0,0.015);
  TH1F* hSigPy = new TH1F("hSigPy", "SigPy", 240,0,0.006);
  TH1F* hBx = new TH1F("hBx", "Bx", 100,-20,20);
  TH1F* hBx1 = new TH1F("hBx1", "Bx1", 100,-20,20);
  TH1F* hBx2 = new TH1F("hBx2", "Bx2", 100,-20,20);
  TH1F* hBy = new TH1F("hBy", "By", 240,-2.5,2.5);
  TH1F* hPchi2 = new TH1F("hPchi2", "Pchi2", 400,0,200);
  TH1F* hXFirst0 = new TH1F("hXFirst0", "XFirst0", 100,-100,100);
  TH1F* hXFirst1 = new TH1F("hXFirst1", "hXFirst1", 100,-100,100);
  TH1F* hXFirst2 = new TH1F("hXFirst2", "hXFirst2", 100,-100,100);
  TH1F* hXFirst3 = new TH1F("hXFirst3", "hXFirst3", 100,-100,100);
  TH1F* hYFirst0 = new TH1F("hYFirst0", "YFirst0", 100,-100,100);
  TH1F* hYFirst1 = new TH1F("hYFirst1", "YFirst1", 100,-100,100);
  TH1F* hYFirst2 = new TH1F("hYFirst2", "YFirst2", 100,-100,100);
  TH1F* hYFirst3 = new TH1F("hYFirst3", "YFirst3", 100,-100,100);
  TH1F* hZFirst0 = new TH1F("hZFirst0", "ZFirst0", 100,-700,700);
  TH1F* hZFirst1 = new TH1F("hZFirst1", "ZFirst1", 100,-700,700);
  TH1F* hZFirst2 = new TH1F("hZFirst2", "ZFirst2", 100,-700,700);
  TH1F* hZFirst3 = new TH1F("hZFirst3", "ZFirst3", 50,-700,700);
  TH1F* hXLast0 = new TH1F("hXLast0", "XLast0", 100,-500,500);
  TH1F* hXLast1 = new TH1F("hXLast1", "hXLast1", 100,-500,500);
  TH1F* hXLast2 = new TH1F("hXLast2", "hXLast2", 100,-500,500);
  TH1F* hXLast3 = new TH1F("hXLast3", "hXLast3", 100,-500,500);
  TH1F* hYLast0 = new TH1F("hYLast0", "YLast0", 100,-500,500);
  TH1F* hYLast1 = new TH1F("hYLast1", "YLast1", 100,-500,500);
  TH1F* hYLast2 = new TH1F("hYLast2", "YLast2", 100,-500,500);
  TH1F* hYLast3 = new TH1F("hYLast3", "YLast3", 100,-500,500);
  TH1F* hZLast0 = new TH1F("hZLast0", "ZLast0", 100,-700,700);
  TH1F* hZLast1 = new TH1F("hZLast1", "ZLast1", 100,-700,700);
  TH1F* hZLast2 = new TH1F("hZLast2", "ZLast2", 100,-700,700);
  TH1F* hZLast3 = new TH1F("hZLast3", "ZLast3", 50,-700,700);
  TH1F* hLabel = new TH1F("hLabel", "Label", 200,0,1000);
  TH1F* hTofX = new TH1F("hTofX", "TofX", 100,-20,20);
  TH1F* hTofY = new TH1F("hTofY", "TofY", 240,-100,100);
  TH1F* hTofPathl = new TH1F("hTofPathl", "TofPathl", 240,-20,20);
  TH1F* hTofCharge = new TH1F("hTofCharge", "TofCharge", 50,-2,2);
  TH1F* hTofMass2 = new TH1F("hTofMass2", "TofMass2", 200,-100,100);
  TH1F* hTofSigMass2 = new TH1F("hTofSigMass2", "TofSigMass2", 100,-10,100);
  
  TH1F* hNRun = new TH1F("hNRun", "number of run", 100,3100,3170);
  TH1F* hNEvent = new TH1F("hNEvent", "number of event", 100,0,360300);
  TH1F* hTriggerMask = new TH1F("hTriggerMask", "trigger mask", 100,-500,500);
  TH1F* hDate = new TH1F("hDate", "date", 100,0,6000);
  TH1F* hTime = new TH1F("hTime", "time", 50,0,100);
  TH1F* hWfaNbeam = new TH1F("hWfaNbeam", "Number of beam particles from WFA channel 1 ", 100,0,10);
  TH1F* hWfaNinter = new TH1F("hWfaNinter", "Number of interactions from WFA channel 2 ", 50,0,5);
  TH1F* hWfaBeamTime = new TH1F("hWfaBeamTime", "WFA time in nsec ", 100,-15000,100);
  TH1F* hWfaInterTime = new TH1F("hWfaInterTime", "WFA time in nsec ", 100,-15000,1000);
  TH1F* hNPrimaryParticles = new TH1F("hNPrimaryParticles", "NPrimaryParticles ", 100,0,1000);
  TH2F* hTracks_vs_Eveto = new TH2F("hTracks_vs_Eveto", "Tracks_vs_Eveto", 200,0,1000, 200,200,10000);
  TH2F* hTracks_vs_VertexZ = new TH2F("hTracks_vs_VertexZ", "Tracks_vs_VertexZ", 150,-602,-560, 200,0,1000);
  TH2F* hVertexZ_vs_Eveto = new TH2F("hVertexZ_vs_Eveto", "VertexZ_vs_Eveto", 200,200,10000, 150,-602,-560);
  
  TH2F* hTracks_vs_Eveto_cuts = new TH2F("hTracks_vs_Eveto_cuts", "Tracks_vs_Eveto_clear", 100,0,1000, 100,200,10000);
  TH2F* hTracks_vs_Eveto_cuts1 = new TH2F("hTracks_vs_Eveto_cuts1", "Tracks_vs_Eveto_clear_full", 100,0,1000, 100,200,10000);
  TH1F* hPrimaryParticles_fIdDet = new TH1F("hPrimaryParticles_fIdDet", "PrimaryParticles_fIdDet", 40,0,40);
 
  TH1F* hPrimaryParticles_fCharge = new TH1F("hPrimaryParticles_fCharge", "charge ", 100,-2,2);
  
  TH1F* hPrimaryParticles_fNPoint_v1tpc = new TH1F("hPrimaryParticles_fNPoint_v1tpc", "NPoint_v1tpc ", 100,0,300);
  TH1F* hPrimaryParticles_fNPoint_v2tpc = new TH1F("hPrimaryParticles_fNPoint_v2tpc", "NPoint_v2tpc ", 100,0,300);
  TH1F* hPrimaryParticles_fNPoint_mtpc = new TH1F("hPrimaryParticles_fNPoint_mtpc", "NPoint_mtpc ", 100,0,300);
  TH1F* hPrimaryParticles_fNPoint = new TH1F("hPrimaryParticles_fNPoint", "NPoint ", 100,0,300);
 

  TH1F* hfPrimaryParticles_fNFitPoint_v1tpc  = new TH1F("hfPrimaryParticles_fNFitPoint_v1tpc ", "NFitPoint_v1tpc  ", 100,0,300);
  TH1F* hfPrimaryParticles_fNFitPoint_v2tpc = new TH1F("hfPrimaryParticles_fNFitPoint_v2tpc", "NFitPoint_v2tpc ", 100,0,300);
  TH1F* hfPrimaryParticles_fNFitPoint_mtpc = new TH1F("hfPrimaryParticles_fNFitPoint_mtpc", "NFitPoint_mtpc ", 100,0,300);
  TH1F* hfPrimaryParticles_fNFitPoint = new TH1F("hfPrimaryParticles_fNFitPoint", "NFitPoint ", 100,0,300);

  TH1F* hPrimaryParticles_fNDedxPoint_v1tpc = new TH1F("hPrimaryParticles_fNDedxPoint_v1tpc", "NDedxPoint_v1tpc ", 100,0,300);
  TH1F* hPrimaryParticles_fNDedxPoint_v2tpc = new TH1F("hPrimaryParticles_fNDedxPoint_v2tpc", "NDedxPoint_v2tpc ", 100,0,300);
  TH1F* hPrimaryParticles_fNDedxPoint_mtpc = new TH1F("hPrimaryParticles_fNDedxPoint_mtpc", "NDedxPoint_mtpc ", 100,0,300);
  TH1F* hPrimaryParticles_fNDedxPoint = new TH1F("hPrimaryParticles_fNDedxPoint", "NDedxPoint ", 100,0,300);

  TH1F* hPrimaryParticles_fNMaxPoint_v1tpc = new TH1F("hPrimaryParticles_fNMaxPoint_v1tpc", "NMaxPoint_v1tpc ", 100,0,300);
  TH1F* hPrimaryParticles_fNMaxPoint_v2tpc = new TH1F("hPrimaryParticles_fNMaxPoint_v2tpc", "NMaxPoint_v2tpc ", 100,0,300);
  TH1F* hPrimaryParticles_fNMaxPoint_mtpc = new TH1F("hPrimaryParticles_fNMaxPoint_mtpc", "NMaxPoint_mtpc", 100,0,300);
  TH1F* hPrimaryParticles_fNMaxPoint = new TH1F("hPrimaryParticles_fNMaxPoint", "NMaxPoint ", 100,0,300);

  TH1F* hPrimaryParticles_fIflag = new TH1F("hPrimaryParticles_fIflag", "fIflag", 100,-500,500);
 
  TH1F* hPrimaryParticles_fTmeanCharge0 = new TH1F("hPrimaryParticles_fTmeanCharge0", "TmeanCharge0", 100,0,2500);
  TH1F* hPrimaryParticles_fTmeanCharge1 = new TH1F("hPrimaryParticles_fTmeanCharge1", "TmeanCharge1", 100,0,2500);
  TH1F* hPrimaryParticles_fTmeanCharge2 = new TH1F("hPrimaryParticles_fTmeanCharge2", "TmeanCharge2", 100,0,2500);
  TH1F* hPrimaryParticles_fTmeanCharge3 = new TH1F("hPrimaryParticles_fTmeanCharge3", "TmeanCharge3", 100,0,2500);
  TH2F* hPrimaryParticles_fTmeanCharge0_vs_p = new TH2F("hPrimaryParticles_fTmeanCharge0_v1tpc_vs_p", "TmeanChargev1tpc_vs_p ",200,0,1000 , 500,0,10000);
  TH2F* hPrimaryParticles_fTmeanCharge1_vs_p = new TH2F("hPrimaryParticles_fTmeanCharge1_v2tpc_vs_p", "TmeanChargev2tpc_vs_p ",200,0,1000, 500,0,10000);
  TH2F* hPrimaryParticles_fTmeanCharge2_vs_p = new TH2F("hPrimaryParticles_fTmeanCharge2_mtpc_vs_p", "TmeanChargemtpc_vs_p ",200,0,1000, 500,0,10000);
  TH2F* hPrimaryParticles_fTmeanCharge3_vs_p = new TH2F("hPrimaryParticles_fTmeanCharge_vs_p", "TmeanCharge_vs_p ",200,0,1000, 500,0,10000);

  TH1F* hVeto_fAdcHadron0 = new TH1F("hVeto_fAdcHadron0", "hVeto_fAdcHadron0", 100,0,10000);
  TH1F* hVeto_fAdcHadron1 = new TH1F("hVeto_fAdcHadron1", "hVeto_fAdcHadron1", 100,0,10000);
  TH1F* hVeto_fAdcHadron2= new TH1F("hVeto_fAdcHadron2", "hVeto_fAdcHadron2", 100,0,10000);
  TH1F* hVeto_fAdcHadron3 = new TH1F("hVeto_fAdcHadron3", "hVeto_fAdcHadron3", 100,0,10000);

  TH1F* hPrimaryParticles_fTofIflag = new TH1F("hPrimaryParticles_fTofIflag", "TofIflag", 100,-100,100);
  TH1F* hPrimaryParticles_fTofId = new TH1F("hPrimaryParticles_fTofId", "TofId", 100,-100,100);

  TH2F* hRingSignals= new TH2F(" hRingSignals", "RingSignals", 240,0,240, 100,0,1200);
  TH1F* hRing_sum_of_Signals= new TH1F("hRing_sum_of_Signals", "Ring_sum_of_Signals", 50,0,1200);
  TH2F* hRing_sum_of_Signals_vs_tracks= new TH2F("hRing_sum_of_Signals_vs_tracks", "Ring_sum_of_Signals_vs_tracks", 200,0,1000, 250,0,1200);
  

  TH1F* hVetoSignals0= new TH1F(" hVetoSignals0", "hVetoSignals0", 100,0,1500);
  TH1F* hVetoSignals1= new TH1F(" hVetoSignals1", "hVetoSignals1", 100,0,1500);
  TH1F* hVetoSignals2= new TH1F(" hVetoSignals2", "hVetoSignals2", 100,0,1500);
  TH1F* hVetoSignals3= new TH1F(" hVetoSignals3", "hVetoSignals3", 100,0,1500);
  TH1F* hNdivideNmax= new TH1F(" hNdivideNmax", "fNPoint/fNMaxPoint", 50,0,1);
  TH2F* hfNPoint_vs_fNMaxPoint = new TH2F(" hfNPoint_vs_fNMaxPoint", "NPoint_vs_NMaxPoint", 250,0,250,250,0,250);
  TH1F* hVertex_fPchi2= new TH1F("hVertex_fPchi2","Vertex_Pchi2",50,-2,1.2);
  TH2F* hTracks_vs_label=new TH2F("hTracks_vs_label","Tracks_vs_label", 100,0,1000,200,0,1000);

 





  const int N_MAX_TRACKS = 1200;
  Int_t fNRun , fNEvent ,fTriggerMask ,fDate ,fTime;
  Float_t  fEveto ,fVertexX ,fVertexY ,fVertexZ;
  Int_t fWfaNbeam,fWfaNinter,fWfaBeamTime,fWfaInterTime,fNPrimaryParticles ; 
  Char_t fPrimaryParticles_fIdDet[N_MAX_TRACKS],fPrimaryParticles_fCharge[N_MAX_TRACKS];
  UChar_t fPrimaryParticles_fNPoint[N_MAX_TRACKS][4], fPrimaryParticles_fNFitPoint[N_MAX_TRACKS][4] , fPrimaryParticles_fNDedxPoint[N_MAX_TRACKS][4] ,fPrimaryParticles_fNMaxPoint[N_MAX_TRACKS][4] ;
  Int_t  fPrimaryParticles_fIflag[N_MAX_TRACKS];
  UShort_t fPrimaryParticles_fTmeanCharge[N_MAX_TRACKS][4];
  Float_t fPrimaryParticles_fPz[N_MAX_TRACKS],fPrimaryParticles_fEta[N_MAX_TRACKS],fPrimaryParticles_fPhi[N_MAX_TRACKS],fPrimaryParticles_fPt[N_MAX_TRACKS], fPrimaryParticles_fSigPx[N_MAX_TRACKS],fPrimaryParticles_fSigPy[N_MAX_TRACKS];
  Float_t fPrimaryParticles_fBx[N_MAX_TRACKS] , fPrimaryParticles_fBy[N_MAX_TRACKS] ,fPrimaryParticles_fPchi2[N_MAX_TRACKS];
  Float_t fPrimaryParticles_fXFirst[N_MAX_TRACKS][4] , fPrimaryParticles_fYFirst[N_MAX_TRACKS][4] ,fPrimaryParticles_fZFirst[N_MAX_TRACKS][4] ;
  Float_t fPrimaryParticles_fXLast[N_MAX_TRACKS][4], fPrimaryParticles_fYLast[N_MAX_TRACKS][4] ,fPrimaryParticles_fZLast[N_MAX_TRACKS][4], fPrimaryParticles_fLabel[N_MAX_TRACKS] ;
  Int_t  fPrimaryParticles_fTofIflag[N_MAX_TRACKS], fPrimaryParticles_fTofId [N_MAX_TRACKS];
  Float_t fPrimaryParticles_fTofX[N_MAX_TRACKS], fPrimaryParticles_fTofY[N_MAX_TRACKS] ,fPrimaryParticles_fTofPathl[N_MAX_TRACKS] ,fPrimaryParticles_fTofCharge[N_MAX_TRACKS],fPrimaryParticles_fTofMass2[N_MAX_TRACKS] ;
  Float_t fPrimaryParticles_fTofSigMass2[N_MAX_TRACKS],   fRing_fADChadron[240];
  Float_t fVeto_fAdcHadron[4];
  Float_t momentum;
  Float_t   fVertex_fPchi2;

 myTree -> Branch("fVertex_fPchi2",&fVertex_fPchi2,"fVertex_fPchi2/F");
 myTree -> Branch("fVeto_fAdcHadron",fVeto_fAdcHadron,"Veto_fAdcHadron[4]/F");
 myTree -> Branch("fNRun",&fNRun,"fNRun/I");
 myTree -> Branch("fNEvent",&fNEvent,"fNEvent/I");
 myTree -> Branch("fTriggerMask",&fTriggerMask,"fTriggerMask/I");
 myTree -> Branch("fDate",&fDate,"fDate/I");
 myTree -> Branch("fTime",&fTime,"fTime/I");

 myTree -> Branch("fEveto",&fEveto,"fEveto/F");
 myTree -> Branch("fVertexX",&fVertexX,"fVertexX/F");
 myTree -> Branch("fVertexY",&fVertexY,"fVertexY/F");
 myTree -> Branch("fVertexZ",&fVertexZ,"fVertexZ/F");

 myTree -> Branch("fWfaNbeam",&fWfaNbeam,"fWfaNbeam/I");
 myTree -> Branch("fWfaNinter",&fWfaNinter,"fWfaNinter/I");
 myTree -> Branch("fWfaBeamTime",&fWfaBeamTime,"fWfaBeamTime/I");
 myTree -> Branch("fWfaInterTime",&fWfaInterTime,"fWfaInterTime/I");
 myTree -> Branch("fNPrimaryParticles",&fNPrimaryParticles,"fNPrimaryParticles/I");

 myTree -> Branch("fPrimaryParticles_fIdDet",fPrimaryParticles_fIdDet,"fPrimaryParticles_fIdDet[fNPrimaryParticles]/B");
 myTree -> Branch("fPrimaryParticles_fCharge",fPrimaryParticles_fCharge,"fPrimaryParticles_fCharge[fNPrimaryParticles]/B");

 myTree -> Branch("fPrimaryParticles_fNPoint",fPrimaryParticles_fNPoint,"fPrimaryParticles_fNPoint[fNPrimaryParticles][4]/b");//  ?
 myTree -> Branch("fPrimaryParticles_fNFitPoint",fPrimaryParticles_fNFitPoint,"fPrimaryParticles_fNFitPoint[fNPrimaryParticles][4]/b");
 myTree -> Branch("fPrimaryParticles_fNDedxPoint",fPrimaryParticles_fNDedxPoint,"fPrimaryParticles_fNDedxPoint[fNPrimaryParticles][4]/b");
 myTree -> Branch("fPrimaryParticles_fNMaxPoint",fPrimaryParticles_fNMaxPoint,"fPrimaryParticles_fNMaxPoint[fNPrimaryParticles][4]/b");

 myTree -> Branch("fPrimaryParticles_fTmeanCharge",fPrimaryParticles_fTmeanCharge,"fPrimaryParticles_fTmeanCharge[fNPrimaryParticles][4]/s");

 myTree -> Branch("fPrimaryParticles_fPz",fPrimaryParticles_fPz,"fPrimaryParticles_fPz[fNPrimaryParticles]/F");
 myTree -> Branch("fPrimaryParticles_fEta",fPrimaryParticles_fEta,"fPrimaryParticles_fEta[fNPrimaryParticles]/F");
 myTree -> Branch("fPrimaryParticles_fPhi",fPrimaryParticles_fPhi,"fPrimaryParticles_fPhi[fNPrimaryParticles]/F");
 myTree -> Branch("fPrimaryParticles_fPt",fPrimaryParticles_fPt,"fPrimaryParticles_fPt[fNPrimaryParticles]/F");
 myTree -> Branch("fPrimaryParticles_fSigPx",fPrimaryParticles_fSigPx,"fPrimaryParticles_fSigPx[fNPrimaryParticles]/F");
 myTree -> Branch("fPrimaryParticles_fSigPy",fPrimaryParticles_fSigPy,"fPrimaryParticles_fSigPy[fNPrimaryParticles]/F");


 myTree -> Branch("fPrimaryParticles_fBx",fPrimaryParticles_fBx,"fPrimaryParticles_fBx[fNPrimaryParticles]/F");
 myTree -> Branch("fPrimaryParticles_fBy",fPrimaryParticles_fBy,"fPrimaryParticles_fBy[fNPrimaryParticles]/F");
 myTree -> Branch("fPrimaryParticles_fPchi2",fPrimaryParticles_fPchi2,"fPrimaryParticles_fPchi2[fNPrimaryParticles]/F");
 
 myTree -> Branch("fPrimaryParticles_fXFirst",fPrimaryParticles_fXFirst,"fPrimaryParticles_fXFirst[fNPrimaryParticles][4]/F");
 myTree -> Branch("fPrimaryParticles_fYFirst",fPrimaryParticles_fYFirst,"fPrimaryParticles_fYFirst[fNPrimaryParticles][4]/F");
 myTree -> Branch("fPrimaryParticles_fZFirst",fPrimaryParticles_fZFirst,"fPrimaryParticles_fZFirst[fNPrimaryParticles][4]/F");
 myTree -> Branch("fPrimaryParticles_fXLast",fPrimaryParticles_fXLast,"fPrimaryParticles_fXLast[fNPrimaryParticles][4]/F");
 myTree -> Branch("fPrimaryParticles_fYLast",fPrimaryParticles_fYLast,"fPrimaryParticles_fYLast[fNPrimaryParticles][4]/F");
 myTree -> Branch("fPrimaryParticles_fZLast",fPrimaryParticles_fZLast,"fPrimaryParticles_fZLast[fNPrimaryParticles][4]/F");

 myTree -> Branch("fPrimaryParticles_fLabel ",fPrimaryParticles_fLabel ,"fPrimaryParticles_fLabel[fNPrimaryParticles] /F");

 myTree -> Branch("fPrimaryParticles_fTofIflag",fPrimaryParticles_fTofIflag,"fPrimaryParticles_fTofIflag[fNPrimaryParticles]/I");
 myTree -> Branch("fPrimaryParticles_fTofId",fPrimaryParticles_fTofId,"fPrimaryParticles_fTofId[fNPrimaryParticles]/I");

 myTree -> Branch("fPrimaryParticles_fTofX",fPrimaryParticles_fTofX,"fPrimaryParticles_fTofX[fNPrimaryParticles]/F");
 myTree -> Branch("fPrimaryParticles_fTofY",fPrimaryParticles_fTofY,"fPrimaryParticles_fTofY[fNPrimaryParticles]/F");
 myTree -> Branch("fPrimaryParticles_fTofPathl",fPrimaryParticles_fTofPathl,"fPrimaryParticles_fTofPathl[fNPrimaryParticles]/F");
 myTree -> Branch("fPrimaryParticles_fTofCharge",fPrimaryParticles_fTofCharge,"fPrimaryParticles_fTofCharge[fNPrimaryParticles]/F");
 myTree -> Branch("fPrimaryParticles_fTofMass2",fPrimaryParticles_fTofMass2,"fPrimaryParticles_fTofMass2[fNPrimaryParticles]/F");
 myTree -> Branch("fPrimaryParticles_fTofSigMass2",fPrimaryParticles_fTofSigMass2,"fPrimaryParticles_fTofSigMass2[fNPrimaryParticles]/F");
 myTree -> Branch("fRing_fADChadron",fRing_fADChadron,"fRing_fADChadron[240]/F"); 


  
  T49Run *run = new T49Run();
  run->SetVerbose(0);

  T49EventRoot *event;
  T49ParticleRoot *particle;
  T49RingRoot *ring;
  T49VertexRoot *vertex;
  T49VetoRoot *veto;
  TObjArray *particles;
  bool runNumberIsSet = false;
  int fileNumber = 0;

  ifstream inputFileListStream(inputFileList);
  string inputFileAddress;
  while (getline(inputFileListStream, inputFileAddress) && fileNumber<maxFileNumber) 
  {	
  	string str2 = inputFileAddress.substr(inputFileAddress.find_last_of("/")+1,inputFileAddress.size());
  	str2=str2.erase(str2.find(".root"),5);
  	str2 ="./" + str2 + "tree.root";
  	
    TFile* outputFileTree = new TFile((Char_t*)str2.c_str(),"RECREATE");
    TTree* tree = myTree->CloneTree();
    //myTree -> Reset();
    fileNumber++;
    cout << "Opening file " << fileNumber << ": " << inputFileAddress.c_str() << endl;
    if(!run -> Open((Char_t*)inputFileAddress.c_str())) continue;
    runNumberIsSet = false;
    while( event = (T49EventRoot *)run -> GetNextEvent() )
    { 

      if (runNumberIsSet==false) 
        {
          run->SetEvetoCal(1);//2 for 160 GeV
          run->SetRunType((Char_t*)runType);
          run->SetRunNumber(event->GetNRun());
          run->CheckEvetoCal();
          runNumberIsSet = true;
          cout << "Run number: " << run->GetRunNumber() << endl;
          cout << "Centrality of first event: " << event->GetCentrality() << endl << endl;
        }
      fNRun = event -> GetNRun();
      fNEvent =event->GetNEvent();
      fTriggerMask =(event->GetTriggerMask());
      fDate=(event->GetDate());
      fTime =(event->GetTime());
      fEveto =(event->GetEveto());
      fVertexX =(event->GetVertexX());
      fVertexY =(event->GetVertexY() );
      fVertexZ =(event->GetVertexZ() );
      fWfaNbeam=(event->GetWfaNbeam());
      fWfaNinter=(event->GetWfaNinter());
      fWfaBeamTime=(event->GetWfaBeamTime() );
      fWfaInterTime=(event->GetWfaInterTime());
      fNPrimaryParticles =(event->GetNParticles(0));
       vertex = ((T49VertexRoot*)event -> GetPrimaryVertex());
        fVertex_fPchi2=(vertex->GetPchi2());
        hVertex_fPchi2->Fill(vertex->GetPchi2());

      hEveto->Fill(event->GetEveto());
      hVertexX->Fill(event->GetVertexX());
      if(-582<=fVertexZ && fVertexZ<=-580)
      hVertexX1 ->Fill(event->GetVertexX());
  
      hVertexY ->Fill(event->GetVertexY());
      if(-582<=fVertexZ && fVertexZ<=-580)
      hVertexY1 ->Fill(event->GetVertexY());
      hVertexXY-> Fill(event->GetVertexX(),event->GetVertexY());

      hVertexZ ->Fill(event->GetVertexZ());
      hNRun ->Fill(event->GetNRun());
  	  hNEvent ->Fill(event->GetNEvent());
  	  hTriggerMask ->Fill(event->GetTriggerMask());
  	  hDate ->Fill(event->GetDate ());
  	  hTime  ->Fill(event->GetTime ());
  	  hWfaNbeam  ->Fill(event->GetWfaNbeam());
  	  hWfaNinter ->Fill(event->GetWfaNinter());
  	  hWfaBeamTime  ->Fill(event->GetWfaBeamTime());
  	  hWfaInterTime ->Fill(event->GetWfaInterTime());
  	  hNPrimaryParticles  ->Fill(event->GetNParticles(0));
  	  hTracks_vs_Eveto ->Fill(event->GetNParticles(0),event->GetEveto());
  	  if(-581.7<=fVertexZ && fVertexZ<=-580.7 && 0.8<=fVertex_fPchi2)
  	  hTracks_vs_Eveto_cuts ->Fill(event->GetNParticles(0),event->GetEveto());
  	  if(fVertex_fPchi2=1)
  	  hTracks_vs_Eveto_cuts1 ->Fill(event->GetNParticles(0),event->GetEveto());
  	  hTracks_vs_VertexZ ->Fill(event->GetVertexZ(),event->GetNParticles(0));
  	  hVertexZ_vs_Eveto ->Fill(event->GetEveto(),event->GetVertexZ());
        

      ring = (T49RingRoot *)event->GetRing();
      for(int i=0;i<240;i++)
      	{
      		fRing_fADChadron[i]=(ring->GetADChadron(i));
      		hRingSignals->Fill(i, ring->GetADChadron(i));
      		hRing_sum_of_Signals->Fill(ring->GetADChadron(i));
  			hRing_sum_of_Signals_vs_tracks->Fill(fNPrimaryParticles,ring->GetADChadron(i));
  		}
      veto = (T49VetoRoot*)event->GetVeto();

        for(int i=0;i<4;i++)
        {
          fVeto_fAdcHadron[i] =(veto->GetADChadron(i));

        }
         
         hVetoSignals0->Fill(veto->GetADChadron(0));
         hVetoSignals1->Fill(veto->GetADChadron(1));
         hVetoSignals2->Fill(veto->GetADChadron(2));
         hVetoSignals3->Fill(veto->GetADChadron(3));

      int k=0;
      particles = (TObjArray*)event -> GetPrimaryParticles();
      TIter particles_iter(particles);
      while( particle = (T49ParticleRoot*) particles_iter.Next())
      {   
        
        
        
        
          
          fPrimaryParticles_fIdDet[k] =(particle->GetIdDet());
          fPrimaryParticles_fCharge[k]  =(particle->GetCharge());
              for(unsigned int j=0;j<3;j++)
                {
                      fPrimaryParticles_fNPoint[k][j]=(particle-> GetNPoint(j));
                      fPrimaryParticles_fNFitPoint[k][j]=(particle-> GetNFitPoint(j));
                      fPrimaryParticles_fNDedxPoint[k][j]=(particle-> GetNDedxPoint(j));
                      fPrimaryParticles_fNMaxPoint[k][j]=(particle->GetNMaxPoint(j));
                      fPrimaryParticles_fTmeanCharge[k][j]=(particle->GetTmeanCharge(j));
                      fPrimaryParticles_fXFirst[k][j]=(particle->GetXFirst(j));
                      fPrimaryParticles_fYFirst[k][j]=(particle->GetYFirst(j));
                      fPrimaryParticles_fZFirst[k][j]=(particle->GetZFirst(j));
                      fPrimaryParticles_fXLast[k][j] =(particle->GetXLast(j));
                      fPrimaryParticles_fYLast[k][j] =(particle->GetYLast(j));
                      fPrimaryParticles_fZLast[k][j] =(particle->GetZLast(j));
                } 
          fPrimaryParticles_fNPoint[k][3]=(particle-> GetNPoint());
          fPrimaryParticles_fNFitPoint[k][3]=(particle-> GetNFitPoint());
          fPrimaryParticles_fNDedxPoint[k][3]=(particle-> GetNDedxPoint());
          fPrimaryParticles_fNMaxPoint[k][3]=(particle->GetNMaxPoint());


    		  if(particle->GetNMaxPoint()!=0)
    		  {
    		  	Float_t div = (particle-> GetNPoint())/(Float_t)(particle->GetNMaxPoint());
    		  hNdivideNmax-> Fill(div);
    		  }	
    		  else hNdivideNmax-> Fill(0);


          fPrimaryParticles_fTmeanCharge[k][3]=(particle->GetTmeanCharge());
          fPrimaryParticles_fXFirst[k][3]=(particle->GetXFirst());
          fPrimaryParticles_fYFirst[k][3]=(particle->GetYFirst());
          fPrimaryParticles_fZFirst[k][3]=(particle->GetZFirst());
          fPrimaryParticles_fXLast[k][3] =(particle->GetXLast());
          fPrimaryParticles_fYLast[k][3] =(particle->GetYLast());
          fPrimaryParticles_fZLast[k][3] =(particle->GetZLast());
          fPrimaryParticles_fPchi2[k]=(particle->GetPchi2());
          fPrimaryParticles_fLabel[k]=(particle->GetLabel());
          fPrimaryParticles_fTofIflag[k]= (particle->GetTofIflag());
          fPrimaryParticles_fTofId[k]=(particle->GetTofId());
          fPrimaryParticles_fIflag[k]=(particle->GetIflag());
          fPrimaryParticles_fPz[k]=(particle->GetPz());
          fPrimaryParticles_fEta[k]=(particle->GetEta());
          fPrimaryParticles_fPhi[k]=(particle->GetPhi());
          fPrimaryParticles_fPt[k]=(particle->GetPt());
          fPrimaryParticles_fSigPx[k]=(particle->GetSigPx());
          fPrimaryParticles_fSigPy[k]=(particle->GetSigPy());
          fPrimaryParticles_fBx[k]=(particle->GetBx());
         
          fPrimaryParticles_fBy[k]=(particle->GetBy());
          fPrimaryParticles_fPchi2[k]=(particle->GetPchi2());
          fPrimaryParticles_fTofX[k]=(particle->GetTofX());
          fPrimaryParticles_fTofY[k]=(particle->GetTofY());
          fPrimaryParticles_fTofPathl[k]=(particle->GetTofPathl()); 
          fPrimaryParticles_fTofCharge[k]=(particle->GetTofCharge());
          fPrimaryParticles_fTofMass2[k] =(particle->GetTofMass2());
          fPrimaryParticles_fTofSigMass2[k] =(particle->GetTofSigMass2());
          k++;
          
        

         

          hPhi->Fill(particle->GetPhi());
          hPt->Fill(particle->GetPt());
          hEta->Fill(particle->GetEta());
          hpt_vs_eta->Fill(particle->GetPt(),particle->GetEta());
          hphi_vs_eta->Fill(particle->GetEta(),particle->GetPhi());
          
          hPz->Fill(particle->GetPz());
          hSigPx ->Fill(particle->GetSigPx());
          hSigPy->Fill(particle->GetSigPy());
          hBx ->Fill(particle->GetBx());
          if(-582<=fVertexZ && fVertexZ<=-580)
     	    hBx1 ->Fill(particle->GetBx());
          hBy ->Fill(particle->GetBy());
          hPchi2->Fill(particle->GetPchi2());
          hXFirst0->Fill(particle->GetXFirst(0));
          hXFirst1->Fill(particle->GetXFirst(1));
          hXFirst2->Fill(particle->GetXFirst(2));
          hXFirst3->Fill(particle->GetXFirst());
          hYFirst0 ->Fill(particle->GetYFirst(0));
          hYFirst1->Fill(particle->GetYFirst(1));
          hYFirst2->Fill(particle->GetYFirst(2));
          hYFirst3->Fill(particle->GetYFirst());
          hZFirst0 ->Fill(particle->GetZFirst(0));
          hZFirst1->Fill(particle->GetZFirst(1));
          hZFirst2->Fill(particle->GetZFirst(2));
          hZFirst3 ->Fill(particle->GetZFirst());
          hXLast0 ->Fill(particle->GetXLast(0));
          hXLast1 ->Fill(particle->GetXLast(1));
          hXLast2 ->Fill(particle->GetXLast(2));
          hXLast3 ->Fill(particle->GetXLast());
          hYLast0->Fill(particle->GetYLast(0));
          hYLast1->Fill(particle->GetYLast(1));
          hYLast2 ->Fill(particle->GetYLast(2));
          hYLast3->Fill(particle->GetYLast());
          hZLast0 ->Fill(particle->GetZLast(0));
          hZLast1 ->Fill(particle->GetZLast(1));
          hZLast2 ->Fill(particle->GetZLast(2));
          hZLast3 ->Fill(particle->GetZLast());
          hLabel ->Fill(particle->GetLabel());
          hTracks_vs_label->Fill(fNPrimaryParticles,particle->GetLabel());
          hTofX ->Fill(particle->GetTofX());
          hTofY ->Fill(particle->GetTofY());
          hTofPathl ->Fill(particle->GetTofPathl());
          hTofCharge ->Fill(particle->GetTofCharge());
          hTofMass2 ->Fill(particle->GetTofMass2());
          hTofSigMass2 ->Fill(particle->GetTofSigMass2());
          
  	    
          hPrimaryParticles_fIdDet ->Fill(particle->GetIdDet());
       
          hPrimaryParticles_fCharge ->Fill(particle->GetCharge());
        
          hPrimaryParticles_fNPoint_v1tpc ->Fill(particle->GetNPoint(0));
          hPrimaryParticles_fNPoint_v2tpc  ->Fill(particle->GetNPoint(1));
          hPrimaryParticles_fNPoint_mtpc  ->Fill(particle->GetNPoint(2));
          hPrimaryParticles_fNPoint  ->Fill(particle->GetNPoint());

          hfPrimaryParticles_fNFitPoint_v1tpc  ->Fill(particle->GetNFitPoint(0));
          hfPrimaryParticles_fNFitPoint_v2tpc ->Fill(particle->GetNFitPoint(1));
          hfPrimaryParticles_fNFitPoint_mtpc ->Fill(particle->GetNFitPoint(2));
          hfPrimaryParticles_fNFitPoint  ->Fill(particle->GetNFitPoint());
          
          hPrimaryParticles_fNDedxPoint_v1tpc ->Fill(particle->GetNDedxPoint(0));
          hPrimaryParticles_fNDedxPoint_v2tpc ->Fill(particle->GetNDedxPoint(1));
          hPrimaryParticles_fNDedxPoint_mtpc  ->Fill(particle->GetNDedxPoint(2));
          hPrimaryParticles_fNDedxPoint ->Fill(particle->GetNDedxPoint());
          
          hPrimaryParticles_fNMaxPoint_v1tpc  ->Fill(particle->GetNMaxPoint(0));
          hPrimaryParticles_fNMaxPoint_v2tpc ->Fill(particle->GetNMaxPoint(1));
          hPrimaryParticles_fNMaxPoint_mtpc  ->Fill(particle->GetNMaxPoint(2));
          hPrimaryParticles_fNMaxPoint  ->Fill(particle->GetNMaxPoint());
          hfNPoint_vs_fNMaxPoint ->Fill(particle->GetNMaxPoint(),particle->GetNPoint());

          hPrimaryParticles_fIflag  ->Fill(particle->GetIflag());
       
          hPrimaryParticles_fTmeanCharge0  ->Fill(particle->GetTmeanCharge(0));
          hPrimaryParticles_fTmeanCharge1 ->Fill(particle->GetTmeanCharge(1));
          hPrimaryParticles_fTmeanCharge2 ->Fill(particle->GetTmeanCharge(2));
          hPrimaryParticles_fTmeanCharge3 ->Fill(particle->GetTmeanCharge());

          momentum=sqrt((particle->GetPt())*(particle->GetPt())+(particle->GetPz())*(particle->GetPz()));

          hPrimaryParticles_fTmeanCharge0_vs_p ->Fill( momentum,particle->GetTmeanCharge(0));
          hPrimaryParticles_fTmeanCharge1_vs_p ->Fill( momentum,particle->GetTmeanCharge(1));
          hPrimaryParticles_fTmeanCharge2_vs_p ->Fill( momentum,particle->GetTmeanCharge(2));
  		  hPrimaryParticles_fTmeanCharge3_vs_p ->Fill( momentum,particle->GetTmeanCharge());
          hPrimaryParticles_fTofIflag  ->Fill(particle->GetTofIflag());
          hPrimaryParticles_fTofId ->Fill(particle->GetTofId());
          
          

        }


     tree -> Fill();
    }
    
    outputFileTree->cd();
  	tree ->Write();
 	  outputFileTree->Close();
    run -> Close(); 
     cout<<"+";
  }
  
 

  outputFile1->cd();
  hBx1 ->Write();
  hVertexX1->Write();
  hVertexY1->Write();
  hfNPoint_vs_fNMaxPoint  ->Write();
  hPrimaryParticles_fTmeanCharge0_vs_p ->Write();
  hPrimaryParticles_fTmeanCharge1_vs_p ->Write();
  hPrimaryParticles_fTmeanCharge2_vs_p ->Write();
  hPrimaryParticles_fTmeanCharge3_vs_p ->Write();
  hRing_sum_of_Signals->Write();
  hRing_sum_of_Signals_vs_tracks->Write();
  hTracks_vs_VertexZ ->Write();
  hVertexZ_vs_Eveto->Write();
  hTracks_vs_label->Write();
  hPhi->Write();
  hPt->Write();
  hEta->Write();
  hEveto->Write();
  hVertexX->Write();
  hVertexY ->Write();
  hVertexXY->Write();
  hVertexZ ->Write();
  hPz->Write();
  hSigPx ->Write();
  hSigPy->Write();
  hBx ->Write();
  hBy ->Write();
  hPchi2->Write();
  hXFirst0->Write();
  hXFirst1->Write();
  hXFirst2->Write();
  hXFirst3->Write();
  hYFirst0 ->Write();
  hYFirst1->Write();
  hYFirst2->Write();
  hYFirst3->Write();
  hZFirst0 ->Write();
  hZFirst1->Write();
  hZFirst2->Write();
  hZFirst3 ->Write();
  hXLast0 ->Write();
  hXLast1 ->Write();
  hXLast2 ->Write();
  hXLast3 ->Write();
  hYLast0->Write();
  hYLast1->Write();
  hYLast2 ->Write();
  hYLast3->Write();
  hZLast0 ->Write();
  hZLast1 ->Write();
  hZLast2 ->Write();
  hZLast3 ->Write();
  hLabel ->Write();
  hTofX ->Write();
  hTofY ->Write();
  hTofPathl ->Write();
  hTofCharge ->Write();
  hTofMass2 ->Write();
  hTofSigMass2 ->Write();
  hVertex_fPchi2->Write();

  hNRun ->Write();
  hNEvent ->Write();
  hTriggerMask ->Write();
  hDate ->Write();
  hTime  ->Write();
  hWfaNbeam  ->Write();
  hWfaNinter ->Write();
  hWfaBeamTime  ->Write();
  hWfaInterTime ->Write();
  hNPrimaryParticles  ->Write();
  hPrimaryParticles_fIdDet ->Write();
 
  hPrimaryParticles_fCharge ->Write();
  
  hPrimaryParticles_fNPoint_v1tpc ->Write();
  hPrimaryParticles_fNPoint_v2tpc  ->Write();
  hPrimaryParticles_fNPoint_mtpc  ->Write();
  hPrimaryParticles_fNPoint  ->Write();

  hfPrimaryParticles_fNFitPoint_v1tpc  ->Write();
  hfPrimaryParticles_fNFitPoint_v2tpc ->Write();
  hfPrimaryParticles_fNFitPoint_mtpc ->Write();
  hfPrimaryParticles_fNFitPoint  ->Write();
  hPrimaryParticles_fNDedxPoint_v1tpc ->Write();
  hPrimaryParticles_fNDedxPoint_v2tpc ->Write();
  hPrimaryParticles_fNDedxPoint_mtpc  ->Write();
  hPrimaryParticles_fNDedxPoint ->Write();
  hPrimaryParticles_fNMaxPoint_v1tpc  ->Write();
  hPrimaryParticles_fNMaxPoint_v2tpc ->Write();
  hPrimaryParticles_fNMaxPoint_mtpc  ->Write();
  hPrimaryParticles_fNMaxPoint  ->Write();

  hPrimaryParticles_fIflag  ->Write();
 
  hPrimaryParticles_fTmeanCharge0  ->Write();
  hPrimaryParticles_fTmeanCharge1 ->Write();
  hPrimaryParticles_fTmeanCharge2 ->Write();
  hPrimaryParticles_fTmeanCharge3 ->Write();

  hPrimaryParticles_fTofIflag  ->Write();
  hPrimaryParticles_fTofId ->Write();
  hRingSignals->Write();
  hVetoSignals0->Write();
  hVetoSignals1->Write();
  hVetoSignals2->Write();
  hVetoSignals3->Write();
  hTracks_vs_Eveto ->Write();
  hTracks_vs_Eveto_cuts ->Write();
  hTracks_vs_Eveto_cuts1->Write();
  hpt_vs_eta->Write();
  hphi_vs_eta->Write();
  hNdivideNmax->Write();
  

  outputFile1->Close();
  //outputFileTree->cd();
  //myTree ->Write();
  //outputFileTree->Close();

  timer.Stop();
  printf("Real time: %f\n",timer.RealTime());
  printf("CPU time: %f\n",timer.CpuTime());
  return 1;
}

int main(int argc, char *argv[])
{
  cout << endl << "----- Simple variables analysis -----" << endl << endl;
  switch (argc)
  {
    case 2:
    return simple_variables(argv[1]);
    break;
    case 3:
    return simple_variables(argv[1], atoi(argv[2]));
    break;
    default:
    cout << "Specify input filelist!" << endl;
    cout<<argv[0]<<"  PRODUCTION_TAG  [N_FILES]"<<endl << endl;
    return 0;
  }
  return 1;
}
