//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//
//			アンテナ形状ヘッダー　　antenna.h
//				ダイポールアンテナ
//
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
//				計算
//////////////////////////////////////////////////////////////////////////////////
void Calculation(void)
{
	//========================================================
	//			ローカル変数
	//========================================================
	//--カウンタ
	int i,j,k,m,n,f,l;

	//--計算で使用する変数
	double rrx , rry , rrz;								//セグメント始点
	double drx , dry , drz;								//セグメント終点
	double ssx , ssy , ssz;								//セグメントの単位ベクトル
	double dcl;											//セグメント長さ

	//--エレメント数関係（ワイヤー本数）
	int n_array;										//ダイポールの本数

	//--各部分の分割数
	int nbun_pole1,nbun_pole2,nbun_pole3,nbun_pole4;	//ダイポールの分割数
	int nbun_pole1_2,nbun_pole2_2,nbun_pole3_2;			//ダイポールの分割数
	
	//--各部のセグメント数
	int n_pole;											//ダイポールのセグメント数

	//--設計値関係
	double naien,gaien,naiderutaL,gaiderutaL,h;
	double r_pole1,r_pole2,r_pole3;						//ダイポールの長さ
	double r_pole1_2,r_pole2_2;				//ダイポールの長さ
	double wire_radius;									//ワイヤー半径
	double M_PI=3.14159265358979323846264338327950288;
	double naihan,gaihan;

	//========================================================
	//			放射界計算設定		単位：(deg)
	//========================================================
	//--計算モード
	AXMODE = 0;			//(0=φ固定, 1=θ固定)

	//--可変軸
	DegDelta =  1.0;	//刻み幅("0.0"禁止)
	DegStart =  -90.0;	//初期角
	DegWidth =  180.0;	//範囲

	//--固定軸
	FixAngle =  90.0 + 315.0;	//固定角度

	//========================================================
	//			設計周波数		FREQ0	(f0)	単位：(Hz)
	//			給電周波数		USEF	(f)		単位：(Hz)
	//========================================================

	

	for(k=0;k<1;k++){//内長さ

		for(l=0;l<1;l++){//外長さ

			for(m=0;m<1;m++){//摂動素子内

				for(n=0;n<1;n++){//摂動素子外
			
					for(f=0;f<1;f++){//周波数




	//--設計周波数設定
	FREQ0 = 1.0 * pow(10.0,9.0);

	//--電源周数設定　
	USEF  = FREQ0 * (1.00+(0.001*f));				//f特とるには係数を変更

	//--設計周波数の自由空間波長
	RAMDA0= C/FREQ0;

	//========================================================
	//			形状値定義
	//			長さはRAMDA0を基準　係数で値定義(○○λ)
	//========================================================

	naien = (0.986+0.001*k) * RAMDA0;
	naiderutaL = (0.066+0.001*m) * RAMDA0;

	gaien = (1.984+0.001*l) * RAMDA0;
	gaiderutaL = (0.057+0.001*n) * RAMDA0;

	h = RAMDA0/16;

	//--長さ
	r_pole1 = naien;
	r_pole2 = naiderutaL;

	r_pole1_2 = gaien;
	r_pole2_2 = gaiderutaL;

	r_pole3 = h;

	//--ワイヤー半径
	wire_radius = RAMDA0/200;

	naihan = r_pole1/(2.0*M_PI);//半径
	gaihan = r_pole1_2/(2.0*M_PI);//半径

	//========================================================
	//			全ワイヤー数	NWIR
	//			セグメント数	NSEG
	//			給電点数		NFED
	//			全電流計算点数	NSEG0
	//			Ｚ装荷数		NLOAD		
	//========================================================

	//--全ワイヤー数設定
	n_array = 14;
	NWIR = n_array;

	//--分割数入力
	nbun_pole1 = 42;									//内円(0~315)
	nbun_pole2 = 6;										//内円(315~360)
	nbun_pole3 = int(r_pole2/(0.02*RAMDA0));			//内摂動素子

	nbun_pole1_2 = 84;									//外円(0~315)int(r_pole1_2*0.875/(0.02*RAMDA0))
	nbun_pole2_2 = 12;									//外円(315~360)int(r_pole1_2*0.125/(0.02*RAMDA0))
	nbun_pole3_2 = int(r_pole2_2/(0.02*RAMDA0));		//外摂動素子

	nbun_pole4 = int(r_pole3/(0.02*RAMDA0));			//給電棒


	//ダイポールの分割数

	//--全セグメント数設定
	n_pole = int(2.0*(nbun_pole1+nbun_pole2+nbun_pole3+1+1+1+nbun_pole1_2+nbun_pole2_2+nbun_pole3_2+1+1+1) + 2.0*(nbun_pole4*2+1+1));

	NSEG = n_pole;						//全セグメント数

	//--全電流計算点数  [NSEG0=NSEG-NWIR]	※書き換え＆削除　不可
	NSEG0 = NSEG - NWIR;

	//--給電点数
	NFED = 2;

	//--インピーダンス装荷数
	NLOAD = 0;

	//========================================================
	//			配列確保と初期化
	//			[放射界計算設定,NWIR,NSEG,NFED,NLOAD]
	//				設定後に関数呼び出し
	//			※書き換え＆削除　不可
	//========================================================
	MakeMatAll();								//配列確保(※コメントアウト禁止※)
	Initialization();							//配列と計算用変数の初期化


	//========================================================
	//			出力ファイル用のパラメータ
	//			PARA1 と PARA2 に値を入力する．
	//========================================================
	PARA1 = r_pole1/RAMDA0;
	PARA2 =	r_pole2/RAMDA0;
	PARA3 = r_pole1_2/RAMDA0;//出力用パラメータ①
	PARA4 = r_pole2_2/RAMDA0;//出力用パラメータ②
	PARA5 = FixAngle;

	//========================================================
	//			設計値入力		単位：(m)
	//			セグメント始点	RX[ ] , RY[ ] , RZ[ ] 
	//			単位ベクトル	SX[ ] , SY[ ] , SZ[ ]
	//			セグメント長	SEGL[ ]
	//========================================================


	i=0;

//------------------------------------------------①円(0~315)---------------------------------------------------------
	for(j = 0; j < nbun_pole1+1; ++j){

		//--始点 終点 セグメント長計算
		rrx = naihan * cos((2.0*M_PI/360)*(45) + (2.0*M_PI/(nbun_pole1+nbun_pole2))*(j+0));										//始点位置計算x
		rry = naihan * sin((2.0*M_PI/360)*(45) + (2.0*M_PI/(nbun_pole1+nbun_pole2))*(j+0));										//始点位置計算y
		rrz = r_pole3 ;	//始点位置計算z
		drx = naihan * cos((2.0*M_PI/360)*(45) + (2.0*M_PI/(nbun_pole1+nbun_pole2))*(j+1));										//終点位置計算x
		dry = naihan * sin((2.0*M_PI/360)*(45) + (2.0*M_PI/(nbun_pole1+nbun_pole2))*(j+1));										//終点位置計算y
		drz = r_pole3 ;		//終点位置計算z
		//--セグメント長 単位方向ベクトルの各成分の計算
		dcl = sqrt( pow( (rrx-drx),2 )
				  + pow( (rry-dry),2 )
				  + pow( (rrz-drz),2 ) );						//セグメント長計算
		ssx = (drx-rrx) / dcl;									//単位ベクトルx
		ssy = (dry-rry) / dcl;									//単位ベクトルy
		ssz = (drz-rrz) / dcl;									//単位ベクトルz
		//--計算結果代入
		RX[i] = rrx;											//始点位置x
		RY[i] = rry;											//始点位置y
		RZ[i] = rrz;											//始点位置z
		SX[i] = ssx;											//単位ベクトルx
		SY[i] = ssy;											//単位ベクトルy
		SZ[i] = ssz;											//単位ベクトルz
		SEGL[i] = dcl;											//セグメント長
		i++;
	}



//------------------------------------------------②円(315~360)---------------------------------------------------------
	for(j = 0; j < nbun_pole2+1; ++j){

		//--始点 終点 セグメント長計算
		rrx = naihan * cos((2.0*M_PI/360)*(0) + (2.0*M_PI/(nbun_pole1+nbun_pole2))*(j+0));											//始点位置計算x
		rry = naihan * sin((2.0*M_PI/360)*(0) + (2.0*M_PI/(nbun_pole1+nbun_pole2))*(j+0));											//始点位置計算y
		rrz = r_pole3 ;		//始点位置計算z
		drx = naihan * cos((2.0*M_PI/360)*(0) + (2.0*M_PI/(nbun_pole1+nbun_pole2))*(j+1));											//終点位置計算x
		dry = naihan * sin((2.0*M_PI/360)*(0) + (2.0*M_PI/(nbun_pole1+nbun_pole2))*(j+1));												//終点位置計算y
		drz = r_pole3 ;		//終点位置計算z
		//--セグメント長 単位方向ベクトルの各成分の計算
		dcl = sqrt( pow( (rrx-drx),2 )
				  + pow( (rry-dry),2 )
				  + pow( (rrz-drz),2 ) );						//セグメント長計算
		ssx = (drx-rrx) / dcl;									//単位ベクトルx
		ssy = (dry-rry) / dcl;									//単位ベクトルy
		ssz = (drz-rrz) / dcl;									//単位ベクトルz
		//--計算結果代入
		RX[i] = rrx;											//始点位置x
		RY[i] = rry;											//始点位置y
		RZ[i] = rrz;											//始点位置z
		SX[i] = ssx;											//単位ベクトルx
		SY[i] = ssy;											//単位ベクトルy
		SZ[i] = ssz;											//単位ベクトルz
		SEGL[i] = dcl;											//セグメント長
		i++;
	}


//------------------------------------------------⑥オーバーラップ:摂動素子------------------------------------------------------------
	for(j = 0; j < 1; ++j){
		//--始点 終点 セグメント長計算
		rrx = naihan * cos((2.0*M_PI/360)*(45) + (2.0*M_PI/(nbun_pole1+nbun_pole2))*(j+1));												//始点位置計算x
		rry = naihan * sin((2.0*M_PI/360)*(45) + (2.0*M_PI/(nbun_pole1+nbun_pole2))*(j+1));											//始点位置計算y 半径
		rrz = r_pole3;		//始点位置計算z
		drx = naihan * cos((2.0*M_PI/360)*(45) + (2.0*M_PI/(nbun_pole1+nbun_pole2))*(j+0));												//終点位置計算x
		dry = naihan * sin((2.0*M_PI/360)*(45) + (2.0*M_PI/(nbun_pole1+nbun_pole2))*(j+0));												//終点位置計算y 半径
		drz = r_pole3;		//終点位置計算z
		//--セグメント長 単位方向ベクトルの各成分の計算
		dcl = sqrt( pow( (rrx-drx),2 )
				  + pow( (rry-dry),2 )
				  + pow( (rrz-drz),2 ) );						//セグメント長計算
		ssx = (drx-rrx) / dcl;									//単位ベクトルx
		ssy = (dry-rry) / dcl;									//単位ベクトルy
		ssz = (drz-rrz) / dcl;									//単位ベクトルz
		//--計算結果代入
		RX[i] = rrx;											//始点位置x
		RY[i] = rry;											//始点位置y
		RZ[i] = rrz;											//始点位置z
		SX[i] = ssx;											//単位ベクトルx
		SY[i] = ssy;											//単位ベクトルy
		SZ[i] = ssz;											//単位ベクトルz
		SEGL[i] = dcl;											//セグメント長
		i++;
	}


//------------------------------------------------③摂動素子------------------------------------------------------------

	for(j = 0; j < nbun_pole3; ++j){
		//--始点 終点 セグメント長計算
		rrx = (naihan - ((j+0) * (r_pole2/nbun_pole3)))*cos((M_PI/180)*(45));										        //始点位置計算x
		rry = (naihan - ((j+0) * (r_pole2/nbun_pole3)))*sin((M_PI/180)*(45)); 												//始点位置計算y
		rrz = r_pole3;		//始点位置計算z
		drx = (naihan - ((j+1) * (r_pole2/nbun_pole3)))*cos((M_PI/180)*(45)); 												//終点位置計算x
		dry = (naihan - ((j+1) * (r_pole2/nbun_pole3)))*sin((M_PI/180)*(45));												//終点位置計算y
		drz = r_pole3;		//終点位置計算z
		//--セグメント長 単位方向ベクトルの各成分の計算
		dcl = sqrt( pow( (rrx-drx),2 )
				  + pow( (rry-dry),2 )
				  + pow( (rrz-drz),2 ) );						//セグメント長計算
		ssx = (drx-rrx) / dcl;									//単位ベクトルx
		ssy = (dry-rry) / dcl;									//単位ベクトルy
		ssz = (drz-rrz) / dcl;									//単位ベクトルz
		//--計算結果代入
		RX[i] = rrx;											//始点位置x
		RY[i] = rry;											//始点位置y
		RZ[i] = rrz;											//始点位置z
		SX[i] = ssx;											//単位ベクトルx
		SY[i] = ssy;											//単位ベクトルy
		SZ[i] = ssz;											//単位ベクトルz
		SEGL[i] = dcl;											//セグメント長
		i++;
	}


//------------------------------------------------外円(0~315)---------------------------------------------------------
	for(j = 0; j < nbun_pole1_2+1; ++j){
		//--始点 終点 セグメント長計算
		rrx = gaihan * cos((2.0*M_PI/360)*(22.5) + (2.0*M_PI/(nbun_pole1_2+nbun_pole2_2))*(j+0));	//始点位置計算x
		rry = gaihan * sin((2.0*M_PI/360)*(22.5) + (2.0*M_PI/(nbun_pole1_2+nbun_pole2_2))*(j+0));										//始点位置計算y
		rrz = r_pole3;																				//始点位置計算z
		drx = gaihan * cos((2.0*M_PI/360)*(22.5) + (2.0*M_PI/(nbun_pole1_2+nbun_pole2_2))*(j+1));										//終点位置計算x
		dry = gaihan * sin((2.0*M_PI/360)*(22.5) + (2.0*M_PI/(nbun_pole1_2+nbun_pole2_2))*(j+1));										//終点位置計算y
		drz = r_pole3;		//終点位置計算z
		//--セグメント長 単位方向ベクトルの各成分の計算
		dcl = sqrt( pow( (rrx-drx),2 )
				  + pow( (rry-dry),2 )
				  + pow( (rrz-drz),2 ) );						//セグメント長計算
		ssx = (drx-rrx) / dcl;									//単位ベクトルx
		ssy = (dry-rry) / dcl;									//単位ベクトルy
		ssz = (drz-rrz) / dcl;									//単位ベクトルz
		//--計算結果代入
		RX[i] = rrx;											//始点位置x
		RY[i] = rry;											//始点位置y
		RZ[i] = rrz;											//始点位置z
		SX[i] = ssx;											//単位ベクトルx
		SY[i] = ssy;											//単位ベクトルy
		SZ[i] = ssz;											//単位ベクトルz
		SEGL[i] = dcl;											//セグメント長
		i++;
	}

//------------------------------------------------外円(315~360)---------------------------------------------------------
	for(j = 0; j < nbun_pole2_2+1; ++j){
		//--始点 終点 セグメント長計算
		rrx = gaihan * cos((2.0*M_PI/360)*(-22.5) + (2.0*M_PI/(nbun_pole1_2+nbun_pole2_2))*(j+0));	//始点位置計算x
		rry = gaihan * sin((2.0*M_PI/360)*(-22.5) + (2.0*M_PI/(nbun_pole1_2+nbun_pole2_2))*(j+0));	//始点位置計算y
		rrz = r_pole3;																				//始点位置計算z
		drx = gaihan * cos((2.0*M_PI/360)*(-22.5) + (2.0*M_PI/(nbun_pole1_2+nbun_pole2_2))*(j+1));	//終点位置計算x
		dry = gaihan * sin((2.0*M_PI/360)*(-22.5) + (2.0*M_PI/(nbun_pole1_2+nbun_pole2_2))*(j+1));	//終点位置計算y
		drz = r_pole3;																				//終点位置計算z
		//--セグメント長 単位方向ベクトルの各成分の計算
		dcl = sqrt( pow( (rrx-drx),2 )
				  + pow( (rry-dry),2 )
				  + pow( (rrz-drz),2 ) );						//セグメント長計算
		ssx = (drx-rrx) / dcl;									//単位ベクトルx
		ssy = (dry-rry) / dcl;									//単位ベクトルy
		ssz = (drz-rrz) / dcl;									//単位ベクトルz
		//--計算結果代入
		RX[i] = rrx;											//始点位置x
		RY[i] = rry;											//始点位置y
		RZ[i] = rrz;											//始点位置z
		SX[i] = ssx;											//単位ベクトルx
		SY[i] = ssy;											//単位ベクトルy
		SZ[i] = ssz;											//単位ベクトルz
		SEGL[i] = dcl;											//セグメント長
		i++;
	}


	//------------------------------------------------オーバーラップ:外摂動素子------------------------------------------------------------
	for(j = 0; j < 1; ++j){
		//--始点 終点 セグメント長計算
		rrx = gaihan * cos((2.0*M_PI/360)*(22.5) + (2.0*M_PI/(nbun_pole1_2+nbun_pole2_2))*(j+1));												//始点位置計算x
		rry = gaihan * sin((2.0*M_PI/360)*(22.5) + (2.0*M_PI/(nbun_pole1_2+nbun_pole2_2))*(j+1));											//始点位置計算y 半径
		rrz = r_pole3;		//始点位置計算z
		drx = gaihan * cos((2.0*M_PI/360)*(22.5) + (2.0*M_PI/(nbun_pole1_2+nbun_pole2_2))*(j+0));												//終点位置計算x
		dry = gaihan * sin((2.0*M_PI/360)*(22.5) + (2.0*M_PI/(nbun_pole1_2+nbun_pole2_2))*(j+0));												//終点位置計算y 半径
		drz = r_pole3;		//終点位置計算z
		//--セグメント長 単位方向ベクトルの各成分の計算
		dcl = sqrt( pow( (rrx-drx),2 )
				  + pow( (rry-dry),2 )
				  + pow( (rrz-drz),2 ) );						//セグメント長計算
		ssx = (drx-rrx) / dcl;									//単位ベクトルx
		ssy = (dry-rry) / dcl;									//単位ベクトルy
		ssz = (drz-rrz) / dcl;									//単位ベクトルz
		//--計算結果代入
		RX[i] = rrx;											//始点位置x
		RY[i] = rry;											//始点位置y
		RZ[i] = rrz;											//始点位置z
		SX[i] = ssx;											//単位ベクトルx
		SY[i] = ssy;											//単位ベクトルy
		SZ[i] = ssz;											//単位ベクトルz
		SEGL[i] = dcl;											//セグメント長
		i++;
	}


//------------------------------------------------外摂動素子------------------------------------------------------------

	for(j = 0; j < nbun_pole3_2; ++j){
		//--始点 終点 セグメント長計算
		rrx = (gaihan - ((j+0) * (r_pole2_2/nbun_pole3_2)))*cos((M_PI/180)*(22.5));										        //始点位置計算x
		rry = (gaihan - ((j+0) * (r_pole2_2/nbun_pole3_2)))*sin((M_PI/180)*(22.5)); 												//始点位置計算y
		rrz = r_pole3;		//始点位置計算z
		drx = (gaihan - ((j+1) * (r_pole2_2/nbun_pole3_2)))*cos((M_PI/180)*(22.5)); 												//終点位置計算x
		dry = (gaihan - ((j+1) * (r_pole2_2/nbun_pole3_2)))*sin((M_PI/180)*(22.5));												//終点位置計算y
		drz = r_pole3;		//終点位置計算z
		//--セグメント長 単位方向ベクトルの各成分の計算
		dcl = sqrt( pow( (rrx-drx),2 )
				  + pow( (rry-dry),2 )
				  + pow( (rrz-drz),2 ) );						//セグメント長計算
		ssx = (drx-rrx) / dcl;									//単位ベクトルx
		ssy = (dry-rry) / dcl;									//単位ベクトルy
		ssz = (drz-rrz) / dcl;									//単位ベクトルz
		//--計算結果代入
		RX[i] = rrx;											//始点位置x
		RY[i] = rry;											//始点位置y
		RZ[i] = rrz;											//始点位置z
		SX[i] = ssx;											//単位ベクトルx
		SY[i] = ssy;											//単位ベクトルy
		SZ[i] = ssz;											//単位ベクトルz
		SEGL[i] = dcl;											//セグメント長
		i++;
	}


//------------------------------------------------⑩反射板------------------------------------------------------------

	for(j = 0; j<nbun_pole1+nbun_pole2+nbun_pole3+1+1+1+nbun_pole1_2+nbun_pole2_2+nbun_pole3_2+1+1+1; ++j){
		//--計算結果代入
		RX[i] = RX[j];											//始点位置x
		RY[i] = RY[j];											//始点位置y
		RZ[i] = (-1.0)*RZ[j];									//始点位置z
		SX[i] = SX[j];											//単位ベクトルx
		SY[i] = SY[j];											//単位ベクトルy
		SZ[i] = (-1.0)*SZ[j];									//単位ベクトルz
		SEGL[i] = SEGL[j];										//セグメント長
		i++;
	}


//------------------------------------------------内円オーバーラップ:給電棒(-z)------------------------------------------------------------
	for(j = 0; j < 1; ++j){
		//--始点 終点 セグメント長計算
		rrx = naihan * cos((2.0*M_PI/360)*(0) + (2.0*M_PI/(nbun_pole1+nbun_pole2))*(j+1));			//始点位置計算x
		rry = naihan * sin((2.0*M_PI/360)*(0) + (2.0*M_PI/(nbun_pole1+nbun_pole2))*(j+1));			//始点位置計算y 半径
		rrz = -r_pole3;																			//始点位置計算z
		drx = naihan * cos((2.0*M_PI/360)*(0) + (2.0*M_PI/(nbun_pole1+nbun_pole2))*(j+0));			//終点位置計算x
		dry = naihan * sin((2.0*M_PI/360)*(0) + (2.0*M_PI/(nbun_pole1+nbun_pole2))*(j+0));			//終点位置計算y 半径
		drz = -r_pole3;		//終点位置計算z
		//--セグメント長 単位方向ベクトルの各成分の計算
		dcl = sqrt( pow( (rrx-drx),2 )
				  + pow( (rry-dry),2 )
				  + pow( (rrz-drz),2 ) );						//セグメント長計算
		ssx = (drx-rrx) / dcl;									//単位ベクトルx
		ssy = (dry-rry) / dcl;									//単位ベクトルy
		ssz = (drz-rrz) / dcl;									//単位ベクトルz
		//--計算結果代入
		RX[i] = rrx;											//始点位置x
		RY[i] = rry;											//始点位置y
		RZ[i] = rrz;											//始点位置z
		SX[i] = ssx;											//単位ベクトルx
		SY[i] = ssy;											//単位ベクトルy
		SZ[i] = ssz;											//単位ベクトルz
		SEGL[i] = dcl;
		i++;
	}

//------------------------------------------------内円給電棒------------------------------------------------------------

	for(j = 0; j < nbun_pole4*2; ++j){
		//--始点 終点 セグメント長計算
		rrx = naihan;												//始点位置計算x
		rry = 0.0;											//始点位置計算y 半径
		rrz = (-1.0)*(r_pole3) + (j+0)*(r_pole3/nbun_pole4);		//始点位置計算z
		drx = naihan;											//終点位置計算x
		dry = 0.0;												//終点位置計算y 半径
		drz = (-1.0)*(r_pole3) + (j+1)*(r_pole3/nbun_pole4);		//終点位置計算z
		//--セグメント長 単位方向ベクトルの各成分の計算
		dcl = sqrt( pow( (rrx-drx),2 )
				  + pow( (rry-dry),2 )
				  + pow( (rrz-drz),2 ) );						//セグメント長計算
		ssx = (drx-rrx) / dcl;									//単位ベクトルx
		ssy = (dry-rry) / dcl;									//単位ベクトルy
		ssz = (drz-rrz) / dcl;									//単位ベクトルz
		//--計算結果代入
		RX[i] = rrx;											//始点位置x
		RY[i] = rry;											//始点位置y
		RZ[i] = rrz;											//始点位置z
		SX[i] = ssx;											//単位ベクトルx
		SY[i] = ssy;											//単位ベクトルy
		SZ[i] = ssz;											//単位ベクトルz
		SEGL[i] = dcl;											//セグメント長
		i++;
	}
	

//------------------------------------------------内円オーバーラップ:給電棒(+z)------------------------------------------------------------
	for(j = 0; j < 1; ++j){
		//--始点 終点 セグメント長計算
		rrx = naihan * cos((2.0*M_PI/360)*(0) + (2.0*M_PI/(nbun_pole1+nbun_pole2))*(j+0));			//始点位置計算x
		rry = naihan * sin((2.0*M_PI/360)*(0) + (2.0*M_PI/(nbun_pole1+nbun_pole2))*(j+0));			//始点位置計算y 半径
		rrz = r_pole3;																			//始点位置計算z
		drx = naihan * cos((2.0*M_PI/360)*(0) + (2.0*M_PI/(nbun_pole1+nbun_pole2))*(j+1));			//終点位置計算x
		dry = naihan * sin((2.0*M_PI/360)*(0) + (2.0*M_PI/(nbun_pole1+nbun_pole2))*(j+1));			//終点位置計算y 半径
		drz = r_pole3;		//終点位置計算z
		//--セグメント長 単位方向ベクトルの各成分の計算
		dcl = sqrt( pow( (rrx-drx),2 )
				  + pow( (rry-dry),2 )
				  + pow( (rrz-drz),2 ) );						//セグメント長計算
		ssx = (drx-rrx) / dcl;									//単位ベクトルx
		ssy = (dry-rry) / dcl;									//単位ベクトルy
		ssz = (drz-rrz) / dcl;									//単位ベクトルz
		//--計算結果代入
		RX[i] = rrx;											//始点位置x
		RY[i] = rry;											//始点位置y
		RZ[i] = rrz;											//始点位置z
		SX[i] = ssx;											//単位ベクトルx
		SY[i] = ssy;											//単位ベクトルy
		SZ[i] = ssz;											//単位ベクトルz
		SEGL[i] = dcl;
		i++;
	}



	//------------------------------------------------外円オーバーラップ:給電棒(-z)------------------------------------------------------------
	for(j = 0; j < 1; ++j){
		//--始点 終点 セグメント長計算
		rrx = gaihan * cos((2.0*M_PI/360)*(0) + (2.0*M_PI/(nbun_pole1_2+nbun_pole2_2))*(j+1));		//始点位置計算x
		rry = gaihan * sin((2.0*M_PI/360)*(0) + (2.0*M_PI/(nbun_pole1_2+nbun_pole2_2))*(j+1));		//始点位置計算y 半径
		rrz = -r_pole3;																	//始点位置計算z
		drx = gaihan * cos((2.0*M_PI/360)*(0) + (2.0*M_PI/(nbun_pole1_2+nbun_pole2_2))*(j+0));		//終点位置計算x
		dry = gaihan * sin((2.0*M_PI/360)*(0) + (2.0*M_PI/(nbun_pole1_2+nbun_pole2_2))*(j+0));		//終点位置計算y 半径
		drz = -r_pole3;																	//終点位置計算z
		//--セグメント長 単位方向ベクトルの各成分の計算
		dcl = sqrt( pow( (rrx-drx),2 )
				  + pow( (rry-dry),2 )
				  + pow( (rrz-drz),2 ) );						//セグメント長計算
		ssx = (drx-rrx) / dcl;									//単位ベクトルx
		ssy = (dry-rry) / dcl;									//単位ベクトルy
		ssz = (drz-rrz) / dcl;									//単位ベクトルz
		//--計算結果代入
		RX[i] = rrx;											//始点位置x
		RY[i] = rry;											//始点位置y
		RZ[i] = rrz;											//始点位置z
		SX[i] = ssx;											//単位ベクトルx
		SY[i] = ssy;											//単位ベクトルy
		SZ[i] = ssz;											//単位ベクトルz
		SEGL[i] = dcl;
		i++;
	}

//------------------------------------------------外円給電棒------------------------------------------------------------

	for(j = 0; j < nbun_pole4*2; ++j){
		//--始点 終点 セグメント長計算
		rrx = gaihan;												//始点位置計算x
		rry = 0.0;													//始点位置計算y 半径
		rrz = (-1.0)*(r_pole3) + (j+0)*(r_pole3/nbun_pole4);		//始点位置計算z
		drx = gaihan;												//終点位置計算x
		dry = 0.0;													//終点位置計算y 半径
		drz = (-1.0)*(r_pole3) + (j+1)*(r_pole3/nbun_pole4);		//終点位置計算z
		//--セグメント長 単位方向ベクトルの各成分の計算
		dcl = sqrt( pow( (rrx-drx),2 )
				  + pow( (rry-dry),2 )
				  + pow( (rrz-drz),2 ) );						//セグメント長計算
		ssx = (drx-rrx) / dcl;									//単位ベクトルx
		ssy = (dry-rry) / dcl;									//単位ベクトルy
		ssz = (drz-rrz) / dcl;									//単位ベクトルz
		//--計算結果代入
		RX[i] = rrx;											//始点位置x
		RY[i] = rry;											//始点位置y
		RZ[i] = rrz;											//始点位置z
		SX[i] = ssx;											//単位ベクトルx
		SY[i] = ssy;											//単位ベクトルy
		SZ[i] = ssz;											//単位ベクトルz
		SEGL[i] = dcl;											//セグメント長
		i++;
	}
	

//------------------------------------------------外円オーバーラップ:給電棒(+z)------------------------------------------------------------
	for(j = 0; j < 1; ++j){
		//--始点 終点 セグメント長計算
		rrx = gaihan * cos((2.0*M_PI/360)*(0) + (2.0*M_PI/(nbun_pole1_2+nbun_pole2_2))*(j+0));	//始点位置計算x
		rry = gaihan * sin((2.0*M_PI/360)*(0) + (2.0*M_PI/(nbun_pole1_2+nbun_pole2_2))*(j+0));	//始点位置計算y 半径
		rrz = r_pole3;																		//始点位置計算z
		drx = gaihan * cos((2.0*M_PI/360)*(0) + (2.0*M_PI/(nbun_pole1_2+nbun_pole2_2))*(j+1));	//終点位置計算x
		dry = gaihan * sin((2.0*M_PI/360)*(0) + (2.0*M_PI/(nbun_pole1_2+nbun_pole2_2))*(j+1));	//終点位置計算y 半径
		drz = r_pole3;																		//終点位置計算z
		//--セグメント長 単位方向ベクトルの各成分の計算
		dcl = sqrt( pow( (rrx-drx),2 )
				  + pow( (rry-dry),2 )
				  + pow( (rrz-drz),2 ) );						//セグメント長計算
		ssx = (drx-rrx) / dcl;									//単位ベクトルx
		ssy = (dry-rry) / dcl;									//単位ベクトルy
		ssz = (drz-rrz) / dcl;									//単位ベクトルz
		//--計算結果代入
		RX[i] = rrx;											//始点位置x
		RY[i] = rry;											//始点位置y
		RZ[i] = rrz;											//始点位置z
		SX[i] = ssx;											//単位ベクトルx
		SY[i] = ssy;											//単位ベクトルy
		SZ[i] = ssz;											//単位ベクトルz
		SEGL[i] = dcl;
		i++;
	}

//--------------------------------------------------------------------------------------------------------------------
	//========================================================
	//			各セグメントのワイヤー半径入力	単位：(m)
	//			RA[ ]		ワイヤー半径
	//========================================================
	for(i = 0; i < NSEG; ++i){
		RA[i] = wire_radius;	
	}

	//========================================================
	//			各エレメント(ワイヤー)毎のセグメント数
	//			SEGN[ ]
	//========================================================
	
	//　↓　オーバーラップ込みで　↓
	SEGN[0] = nbun_pole1 +1;
	SEGN[1] = nbun_pole2 +1;
	SEGN[2] = nbun_pole3 +1;

	SEGN[3] = nbun_pole1_2 +1;
	SEGN[4] = nbun_pole2_2 +1;
	SEGN[5] = nbun_pole3_2 +1;

	SEGN[6] = nbun_pole1 +1;
	SEGN[7] = nbun_pole2 +1;
	SEGN[8] = nbun_pole3 +1;

	SEGN[9] = nbun_pole1_2 +1;
	SEGN[10] = nbun_pole2_2 +1;
	SEGN[11] = nbun_pole3_2 +1;

	SEGN[12] = nbun_pole4*2 +2;
	SEGN[13] = nbun_pole4*2 +2;

	
	//========================================================
	//			給電関係設定
	//			給電位置		FEDP[ ]
	//			給電電圧		FEDV[ ]
	//
	//			※位置  FEDP[ ]
	//					[給電したい位置]-[給電したいワイヤー(何番目)]
	//			※電圧  FEDV[ ]
	//				①第１給電の電圧
	//					不平衡給電を用いる場合   -2×(1+j0)[V]
	//					平衡給電を用いる場合     -1×(1+j0)[V]
	//				②反射板付きダイポール等(反射板付き平衡給電アンテナ)
	//					第１給電(反射板表側)   -1×(1+j0)[V]
	//					第２給電(反射板裏側)    1×(1+j0)[V]
	//						(反射板の表と裏で給電位相を逆にする)
	//				③第１給電がイメージ法の場合
	//					他の給電点もイメージ法を適用する．
	//				④第１給電がイメージ法を用いない場合
	//					他の給電点もイメージ法を用いない．
	//				⑤複数給電の電圧・位相差制御
	//					第１給電は条件①②を適用
	//					第１給電以外で制御を行う．
	//========================================================
	FEDP[0] = SEGN[0]+SEGN[1]+SEGN[2]+SEGN[3]+SEGN[4]+SEGN[5]+SEGN[6]+SEGN[7]+SEGN[8]+SEGN[9]+SEGN[10]+SEGN[11]-12+(SEGN[12]-2)/2+1-1;
	FEDP[1] = SEGN[0]+SEGN[1]+SEGN[2]+SEGN[3]+SEGN[4]+SEGN[5]+SEGN[6]+SEGN[7]+SEGN[8]+SEGN[9]+SEGN[10]+SEGN[11]+SEGN[12]-14+(SEGN[13]-2)/2+1-1+1;
	FEDV[0] = -2.0 * Complex( 1.0 , 0.0 );
	FEDV[1] = -2.0 * Complex( 0.70710678118 , -0.70710678118 );

	//========================================================
	//			インピーダンス装荷関係設定
	//			装荷位置		LOADP[ ]
	//			装荷値　		LOADZ[ ]
	//
	//			※位置    LOADP[ ]
	//					[装荷したい位置]-[装荷したいワイヤー(何番目)]
	//			※装荷値　LOADZ[ ]  (50Ωを接続する場合)
	//				①反射板に抵抗を付ける場合		 -2×(50+j0)[Ω]
	//				②ラインの途中に抵抗を付ける場合 -1×(50+j0)[Ω]
	//				③接続対象によらず，値は「マイナス(-)」になる
	//								(抵抗値はベクトルでは無いため)
	//========================================================


	//========================================================
	//			各セグメントからの放射状態を設定(部分放射設定)
	//			RAD_MODE[ ] = 1 or 0
	//				(0 : 放射カット   1 : 通常の放射)
	//			初期化で全てRAD_MODE[ ]=1 に設定済み
	//========================================================


	//========================================================
	//			電流・放射界計算
	//========================================================	
	ConfCheck();				//形状検査
	MakeZmn();					//Zmn作成
	MakeCurrent();				//電流計算
	MakePhase();				//電流位相計算
	Radiation();				//放射界計算
	LapsedTime();				//経過時間取得

	//========================================================
	//			データ出力
	//========================================================	
	OutputConf();				//形状出力
	OutputCurrent();			//電流出力
	OutputRad();				//放射界出力
	OutputChara();				//特性データ出力


	//========================================================
	//			配列の開放
	//========================================================	
	DelMatAll();				//配列開放(※コメントアウト禁止※)
}

}
}
}
}
}
//============================================================================
//					変数と配列一覧
//============================================================================
//
//--形状 給電
//		double	FREQ0					設計周波数f0
//		double	RAMDA0					設計周波数の自由空間波長
//		double	USEF					給電周波数
//		int		NWIR					全ワイヤー数
//		int		NSEG					全セグメント数
//		int		NFED					全給電点数
//		int		NSEG0					全電流計算点数
//		int		NLOAD					抵抗等装荷数
//--放射界計算
//		int		AXMODE   				(0=φ固定, 1=θ固定)	
//		double	DegDelta 				刻み幅
//		double	DegStart 				初期角
//		double	DegWidth 				範囲
//		double	FixAngle 				固定軸角度
//--時間測定
//		int		la_min	la_sec			分 秒
//--計算回し用パラメータ
//		double	PARA1,PARA2				パラメータ①と②
//--形状配列
//		double	RX[ ]  RY[ ]  RZ[ ]		各セグメントの始点
//		double　SX[ ]  SY[ ]  SZ[ ]		単位ベクトルの成分
//		double	SEGL[ ]	RA[ ]			各セグメントの長さ 半径　		
//		int　	SEGN[ ]					各ワイヤーのセグメント数
//		int		FEDP[ ]					各給電位置
//		complex	FEDV[ ]					各給電電圧
//		int		RAD_MODE[ ]				各セグメントの放射モード
//		int		LOADP[ ]				各インピーダンス装荷位置
//		complex LOADZ[ ]				各インピーダンス装荷値
//--電流配列
//		complex Zmn[ ][ ]				インピーダンス行列	
//		complex Im[ ]					電流分布
//		double  PhaseIm[ ]				電流の位相
//--入力インピーダンス
//		complex Zin[ ]					各給電点の入力インピーダンス
//		double  VSWR_50[ ]  VSWR_75[ ]	各給電点の50Ωと75Ωに対するVSWR
//--放射界配列
//		complex TRAD[ ] FRAD[ ]			EθとEφの放射界
//		complex RRAD[ ] LRAD[ ]			ER とEL の放射界
//		double TPHASE[ ] FPHASE[ ]		EθとEφの位相
//		double RPHASE[ ] LPHASE[ ]		ER とEL の位相
//		double TGAI[ ] FGAI[ ]			EθとEφの利得
//		double TFGAI[ ]					EθとEφの合計の利得
//		double RLGAI[ ]					ER とEL の合計の利得
//		double RGAI[ ] LGAI[ ]			ER とEL の利得
//		double TPAT[ ] FPAT[ ]			EθとEφのパターン
//		double RPAT[ ] LPAT[ ]			ER とEL のパターン
//		double AR[ ]					軸比
//--基本物理定数
//		double PI						π
//		double C						光速
//		double e0						真空中の透磁率ε0
//		double u0						真空中の誘電率μ0
//		double R						1.0 固定
//--式簡略用
//		complex J						虚数単位　J=√-1
//--積分用
//		int GaussTenNo					ガウス積分分点  [ 4固定]（通常用）
//		int GaussTenSpe					ガウス積分分点数[40固定]（特異点用）
//--計算用
//		double k0						k0
//		complex uair					u(air)
//		double Beta;					β
//============================================================================