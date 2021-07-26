{
//========= Macro generated from object: cID_Z1_AoQ4/
//========= by ROOT version6.18/04
   
   TCutG *cutg = new TCutG("cID_Z1_AoQ4",9);
   cutg->SetVarX("");
   cutg->SetVarY("");
   cutg->SetTitle("");

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#ffcc00");
   cutg->SetFillColor(ci);
   cutg->SetFillStyle(3444);

   ci = TColor::GetColor("#ffcc00");
   cutg->SetLineColor(ci);
   cutg->SetPoint(0,2.56319,73.9661);
   cutg->SetPoint(1,2.55938,73.8143);
   cutg->SetPoint(2,2.55862,73.3401);
   cutg->SetPoint(3,2.56147,73.1314);
   cutg->SetPoint(4,2.56624,73.1314);
   cutg->SetPoint(5,2.56833,73.4539);
   cutg->SetPoint(6,2.56681,73.8333);
   cutg->SetPoint(7,2.56319,73.9661);
   cutg->SetPoint(8,2.56319,73.9661);
   cutg->Draw("");
}
