void multi_acc_puntiforme(){
	int j,i,n_estrazioni = 1e7,n_hit,n_punti=200;
	int N_BIN = 100;
	float R =1.0,D=0.1,INC=0.05; //cm
	float rho,phi,theta,x,y,z,max_sin_theta,sin_theta,acc_geo,acc_err;
	TStopwatch t_calcolo;
	TF1 *ftheta = new TF1("ftheta","sin(x)",0,TMath::Pi()/2);
	TF1 *fD = new TF1("fD","1/(4*x*x)",0.1,8);
	//fD->FixParameter(0,R);
	TGraph *gr = new TGraph();
	TGraphErrors *gr1 = new TGraphErrors();
	for(j=0;j<n_punti;j++,D=D+INC)
	{
		max_sin_theta=R/sqrt(D*D+R*R);
	for(i=0,n_hit=0;i<n_estrazioni;i++)
	{
		theta = ftheta->GetRandom(0,TMath::Pi()/2);
		sin_theta = sin(theta);
		if(sin_theta<=max_sin_theta)
		{
			n_hit++;
		}
	}
	acc_geo = ((float)n_hit)/(2*n_estrazioni);
	acc_err = acc_err*acc_geo;
	acc_err = sqrt((1/(float)n_estrazioni)+(1/(float)n_hit));
	gr->SetPoint(j,D,acc_geo);
	gr1->SetPoint(j,D,acc_geo);
	gr1->SetPointError(j,0,acc_err);
	}
	TCanvas *c1 = new TCanvas("c1");
	gr->Draw("AP");
	gr->SetTitle("Accettanza Geometrica Sorgente Puntiforme");
	gr->GetXaxis()->SetTitle("Distanza Rivelatore [cm]");
	gr->GetXaxis()->SetRangeUser(0,8);
	//gr->GetYaxis()->SetRangeUser(0,5);
	gr->GetYaxis()->SetTitle("Accettanza Geometrica");
	gr->SetMarkerColor(kRed);
	gr->SetMarkerStyle(3);
	fD->Draw("same");
	fD->SetLineColor(kBlue);
	c1->SaveAs("acc_dist.png");
	
	TCanvas *c2 = new TCanvas("c2");
	gr1->Draw("AP");
	gr1->SetTitle("Accettanza Geometrica Sorgente Puntiforme con Errori");
	gr1->GetXaxis()->SetTitle("Distanza Rivelatore [cm]");
	gr1->GetXaxis()->SetRangeUser(0,8);
	gr1->GetYaxis()->SetTitle("Accettanza Geometrica");
	gr1->SetMarkerColor(kRed);
	gr1->SetMarkerStyle(3);
	fD->Draw("same");
	fD->SetLineColor(kBlue);
	//gr->Fit(fD);
	//gr1->Fit(fD);
	c2->SaveAs("acc_dist_err.jpg");
}