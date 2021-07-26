{
//========= Macro generated from object: cID_Z1_AoQ6/
//========= by ROOT version6.18/04
   
   TCutG *cutg = new TCutG("cID_Z1_AoQ6",8);
   cutg->SetVarX("");
   cutg->SetVarY("");
   cutg->SetTitle("");

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#ff0000");
   cutg->SetFillColor(ci);
   cutg->SetFillStyle(3444);

   ci = TColor::GetColor("#ff0000");
   cutg->SetLineColor(ci);
   cutg->SetPoint(0,2.55916,73.4464);
   cutg->SetPoint(1,2.57165,73.4848);
   cutg->SetPoint(2,2.57363,73.1267);
   cutg->SetPoint(3,2.57202,72.5897);
   cutg->SetPoint(4,2.55854,72.628);
   cutg->SetPoint(5,2.55916,73.4464);
   cutg->SetPoint(6,2.55916,73.4464);
   cutg->SetPoint(7,2.55916,73.4464);
   cutg->Draw("");
}
