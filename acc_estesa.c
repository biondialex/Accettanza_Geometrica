void acc_estesa(){
	int i,n_estrazioni = 1e7,n_hit;
	int N_BIN = 100;
	float R_RIL =1.0,R_SOR=0.5,D=5,EST1 = D+1,EST2 = R_RIL+0.5,R_SFE=5; //cm
	float rho,phi,psi,theta,x,y,z,max_sin_theta,sin_theta,acc_geo,acc_err;
	TStopwatch t_calcolo;
	TF1 *frho = new TF1("frho","x",0,R_SOR);
	TF1 *ftheta = new TF1("ftheta","sin(x)",0,TMath::Pi()/2);
	TH3F *h1 = new TH3F("sfera","Emissione Sorgente a Moneta",N_BIN,-EST1,EST1,N_BIN,-EST1,EST1,N_BIN,-EST1,EST1);
	TH2F *h2 = new TH2F("rivelatore","Intersezione Piano Rivelatore",N_BIN,-EST2,EST2,N_BIN,-EST2,EST2);
	t_calcolo.Start();
	for(i=0,n_hit=0;i<n_estrazioni;i++)
	{
		psi = gRandom->Uniform(0,2*TMath::Pi()); //Genero punto che emette sulla sorg
		rho = frho->GetRandom(0,R_SOR);
		//rho=0; //Condizione di Sorgente puntiforme
		theta = ftheta->GetRandom(0,TMath::Pi()/2);
		sin_theta = sin(theta);
		max_sin_theta = (R_RIL-rho)/sqrt((D*D)+((R_RIL-rho)*(R_RIL-rho)));
		
		phi = gRandom->Uniform(0,2*TMath::Pi());
		psi = gRandom->Uniform(0,2*TMath::Pi()); 
		x = rho*cos(psi)+R_SFE*sin(theta)*cos(phi);
		y = rho*sin(psi)+R_SFE*sin(theta)*sin(phi);
		z = R_SFE*cos(theta);
		h1->Fill(x,y,z);
		
		
		if(sin_theta<=max_sin_theta)
		{
			phi = gRandom->Uniform(0,2*TMath::Pi());
			x = (D*tan(theta))*cos(phi);
			y = (D*tan(theta))*sin(phi);
			n_hit++;
			h2->Fill(x,y);
		}
	}
	t_calcolo.Stop();
	acc_geo = ((float)n_hit)/(2*n_estrazioni);
	acc_err = sqrt((1/(float)n_estrazioni)+(1/(float)n_hit));
	cout<<"N_hit = "<<n_hit<<"\nErrore Relativo: "<<acc_err<<"\n"<<endl;
	acc_err = acc_err*acc_geo;
	cout << "Accettanza Geometrica: "<<acc_geo<< "+- "<<acc_err<<endl;
	t_calcolo.Print("m");
	TCanvas *c1 = new TCanvas("c1","",500,500);
	h2->Draw("colz");
	h2->GetXaxis()->SetTitle("X");
	h2->GetYaxis()->SetTitle("Y");
	c1->SaveAs("acc_moneta_rivelatore.png");
	
	TCanvas *c2 = new TCanvas("c2","",700,700);
	h1->Draw("");
	h1->GetXaxis()->SetTitle("X");
	h1->GetYaxis()->SetTitle("Y");
	h1->GetZaxis()->SetTitle("Z");
	c2->SaveAs("acc_moneta_sfera.png");
	
}