//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//
//			�A���e�i�`��w�b�_�[�@�@antenna.h
//				�_�C�|�[���A���e�i
//
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
//				�v�Z
//////////////////////////////////////////////////////////////////////////////////
void Calculation(void)
{
	//========================================================
	//			���[�J���ϐ�
	//========================================================
	//--�J�E���^
	int i,j,k,m,n,f,l;

	//--�v�Z�Ŏg�p����ϐ�
	double rrx , rry , rrz;								//�Z�O�����g�n�_
	double drx , dry , drz;								//�Z�O�����g�I�_
	double ssx , ssy , ssz;								//�Z�O�����g�̒P�ʃx�N�g��
	double dcl;											//�Z�O�����g����

	//--�G�������g���֌W�i���C���[�{���j
	int n_array;										//�_�C�|�[���̖{��

	//--�e�����̕�����
	int nbun_pole1,nbun_pole2,nbun_pole3,nbun_pole4;	//�_�C�|�[���̕�����
	int nbun_pole1_2,nbun_pole2_2,nbun_pole3_2;			//�_�C�|�[���̕�����
	
	//--�e���̃Z�O�����g��
	int n_pole;											//�_�C�|�[���̃Z�O�����g��

	//--�݌v�l�֌W
	double naien,gaien,naiderutaL,gaiderutaL,h;
	double r_pole1,r_pole2,r_pole3;						//�_�C�|�[���̒���
	double r_pole1_2,r_pole2_2;				//�_�C�|�[���̒���
	double wire_radius;									//���C���[���a
	double M_PI=3.14159265358979323846264338327950288;
	double naihan,gaihan;

	//========================================================
	//			���ˊE�v�Z�ݒ�		�P�ʁF(deg)
	//========================================================
	//--�v�Z���[�h
	AXMODE = 0;			//(0=�ӌŒ�, 1=�ƌŒ�)

	//--�ώ�
	DegDelta =  1.0;	//���ݕ�("0.0"�֎~)
	DegStart =  -90.0;	//�����p
	DegWidth =  180.0;	//�͈�

	//--�Œ莲
	FixAngle =  90.0 + 315.0;	//�Œ�p�x

	//========================================================
	//			�݌v���g��		FREQ0	(f0)	�P�ʁF(Hz)
	//			���d���g��		USEF	(f)		�P�ʁF(Hz)
	//========================================================

	

	for(k=0;k<1;k++){//������

		for(l=0;l<1;l++){//�O����

			for(m=0;m<1;m++){//�ۓ��f�q��

				for(n=0;n<1;n++){//�ۓ��f�q�O
			
					for(f=0;f<1;f++){//���g��




	//--�݌v���g���ݒ�
	FREQ0 = 1.0 * pow(10.0,9.0);

	//--�d�������ݒ�@
	USEF  = FREQ0 * (1.00+(0.001*f));				//f���Ƃ�ɂ͌W����ύX

	//--�݌v���g���̎��R��Ԕg��
	RAMDA0= C/FREQ0;

	//========================================================
	//			�`��l��`
	//			������RAMDA0����@�W���Œl��`(������)
	//========================================================

	naien = (0.986+0.001*k) * RAMDA0;
	naiderutaL = (0.066+0.001*m) * RAMDA0;

	gaien = (1.984+0.001*l) * RAMDA0;
	gaiderutaL = (0.057+0.001*n) * RAMDA0;

	h = RAMDA0/16;

	//--����
	r_pole1 = naien;
	r_pole2 = naiderutaL;

	r_pole1_2 = gaien;
	r_pole2_2 = gaiderutaL;

	r_pole3 = h;

	//--���C���[���a
	wire_radius = RAMDA0/200;

	naihan = r_pole1/(2.0*M_PI);//���a
	gaihan = r_pole1_2/(2.0*M_PI);//���a

	//========================================================
	//			�S���C���[��	NWIR
	//			�Z�O�����g��	NSEG
	//			���d�_��		NFED
	//			�S�d���v�Z�_��	NSEG0
	//			�y���א�		NLOAD		
	//========================================================

	//--�S���C���[���ݒ�
	n_array = 14;
	NWIR = n_array;

	//--����������
	nbun_pole1 = 42;									//���~(0~315)
	nbun_pole2 = 6;										//���~(315~360)
	nbun_pole3 = int(r_pole2/(0.02*RAMDA0));			//���ۓ��f�q

	nbun_pole1_2 = 84;									//�O�~(0~315)int(r_pole1_2*0.875/(0.02*RAMDA0))
	nbun_pole2_2 = 12;									//�O�~(315~360)int(r_pole1_2*0.125/(0.02*RAMDA0))
	nbun_pole3_2 = int(r_pole2_2/(0.02*RAMDA0));		//�O�ۓ��f�q

	nbun_pole4 = int(r_pole3/(0.02*RAMDA0));			//���d�_


	//�_�C�|�[���̕�����

	//--�S�Z�O�����g���ݒ�
	n_pole = int(2.0*(nbun_pole1+nbun_pole2+nbun_pole3+1+1+1+nbun_pole1_2+nbun_pole2_2+nbun_pole3_2+1+1+1) + 2.0*(nbun_pole4*2+1+1));

	NSEG = n_pole;						//�S�Z�O�����g��

	//--�S�d���v�Z�_��  [NSEG0=NSEG-NWIR]	�������������폜�@�s��
	NSEG0 = NSEG - NWIR;

	//--���d�_��
	NFED = 2;

	//--�C���s�[�_���X���א�
	NLOAD = 0;

	//========================================================
	//			�z��m�ۂƏ�����
	//			[���ˊE�v�Z�ݒ�,NWIR,NSEG,NFED,NLOAD]
	//				�ݒ��Ɋ֐��Ăяo��
	//			�������������폜�@�s��
	//========================================================
	MakeMatAll();								//�z��m��(���R�����g�A�E�g�֎~��)
	Initialization();							//�z��ƌv�Z�p�ϐ��̏�����


	//========================================================
	//			�o�̓t�@�C���p�̃p�����[�^
	//			PARA1 �� PARA2 �ɒl����͂���D
	//========================================================
	PARA1 = r_pole1/RAMDA0;
	PARA2 =	r_pole2/RAMDA0;
	PARA3 = r_pole1_2/RAMDA0;//�o�͗p�p�����[�^�@
	PARA4 = r_pole2_2/RAMDA0;//�o�͗p�p�����[�^�A
	PARA5 = FixAngle;

	//========================================================
	//			�݌v�l����		�P�ʁF(m)
	//			�Z�O�����g�n�_	RX[ ] , RY[ ] , RZ[ ] 
	//			�P�ʃx�N�g��	SX[ ] , SY[ ] , SZ[ ]
	//			�Z�O�����g��	SEGL[ ]
	//========================================================


	i=0;

//------------------------------------------------�@�~(0~315)---------------------------------------------------------
	for(j = 0; j < nbun_pole1+1; ++j){

		//--�n�_ �I�_ �Z�O�����g���v�Z
		rrx = naihan * cos((2.0*M_PI/360)*(45) + (2.0*M_PI/(nbun_pole1+nbun_pole2))*(j+0));										//�n�_�ʒu�v�Zx
		rry = naihan * sin((2.0*M_PI/360)*(45) + (2.0*M_PI/(nbun_pole1+nbun_pole2))*(j+0));										//�n�_�ʒu�v�Zy
		rrz = r_pole3 ;	//�n�_�ʒu�v�Zz
		drx = naihan * cos((2.0*M_PI/360)*(45) + (2.0*M_PI/(nbun_pole1+nbun_pole2))*(j+1));										//�I�_�ʒu�v�Zx
		dry = naihan * sin((2.0*M_PI/360)*(45) + (2.0*M_PI/(nbun_pole1+nbun_pole2))*(j+1));										//�I�_�ʒu�v�Zy
		drz = r_pole3 ;		//�I�_�ʒu�v�Zz
		//--�Z�O�����g�� �P�ʕ����x�N�g���̊e�����̌v�Z
		dcl = sqrt( pow( (rrx-drx),2 )
				  + pow( (rry-dry),2 )
				  + pow( (rrz-drz),2 ) );						//�Z�O�����g���v�Z
		ssx = (drx-rrx) / dcl;									//�P�ʃx�N�g��x
		ssy = (dry-rry) / dcl;									//�P�ʃx�N�g��y
		ssz = (drz-rrz) / dcl;									//�P�ʃx�N�g��z
		//--�v�Z���ʑ��
		RX[i] = rrx;											//�n�_�ʒux
		RY[i] = rry;											//�n�_�ʒuy
		RZ[i] = rrz;											//�n�_�ʒuz
		SX[i] = ssx;											//�P�ʃx�N�g��x
		SY[i] = ssy;											//�P�ʃx�N�g��y
		SZ[i] = ssz;											//�P�ʃx�N�g��z
		SEGL[i] = dcl;											//�Z�O�����g��
		i++;
	}



//------------------------------------------------�A�~(315~360)---------------------------------------------------------
	for(j = 0; j < nbun_pole2+1; ++j){

		//--�n�_ �I�_ �Z�O�����g���v�Z
		rrx = naihan * cos((2.0*M_PI/360)*(0) + (2.0*M_PI/(nbun_pole1+nbun_pole2))*(j+0));											//�n�_�ʒu�v�Zx
		rry = naihan * sin((2.0*M_PI/360)*(0) + (2.0*M_PI/(nbun_pole1+nbun_pole2))*(j+0));											//�n�_�ʒu�v�Zy
		rrz = r_pole3 ;		//�n�_�ʒu�v�Zz
		drx = naihan * cos((2.0*M_PI/360)*(0) + (2.0*M_PI/(nbun_pole1+nbun_pole2))*(j+1));											//�I�_�ʒu�v�Zx
		dry = naihan * sin((2.0*M_PI/360)*(0) + (2.0*M_PI/(nbun_pole1+nbun_pole2))*(j+1));												//�I�_�ʒu�v�Zy
		drz = r_pole3 ;		//�I�_�ʒu�v�Zz
		//--�Z�O�����g�� �P�ʕ����x�N�g���̊e�����̌v�Z
		dcl = sqrt( pow( (rrx-drx),2 )
				  + pow( (rry-dry),2 )
				  + pow( (rrz-drz),2 ) );						//�Z�O�����g���v�Z
		ssx = (drx-rrx) / dcl;									//�P�ʃx�N�g��x
		ssy = (dry-rry) / dcl;									//�P�ʃx�N�g��y
		ssz = (drz-rrz) / dcl;									//�P�ʃx�N�g��z
		//--�v�Z���ʑ��
		RX[i] = rrx;											//�n�_�ʒux
		RY[i] = rry;											//�n�_�ʒuy
		RZ[i] = rrz;											//�n�_�ʒuz
		SX[i] = ssx;											//�P�ʃx�N�g��x
		SY[i] = ssy;											//�P�ʃx�N�g��y
		SZ[i] = ssz;											//�P�ʃx�N�g��z
		SEGL[i] = dcl;											//�Z�O�����g��
		i++;
	}


//------------------------------------------------�E�I�[�o�[���b�v:�ۓ��f�q------------------------------------------------------------
	for(j = 0; j < 1; ++j){
		//--�n�_ �I�_ �Z�O�����g���v�Z
		rrx = naihan * cos((2.0*M_PI/360)*(45) + (2.0*M_PI/(nbun_pole1+nbun_pole2))*(j+1));												//�n�_�ʒu�v�Zx
		rry = naihan * sin((2.0*M_PI/360)*(45) + (2.0*M_PI/(nbun_pole1+nbun_pole2))*(j+1));											//�n�_�ʒu�v�Zy ���a
		rrz = r_pole3;		//�n�_�ʒu�v�Zz
		drx = naihan * cos((2.0*M_PI/360)*(45) + (2.0*M_PI/(nbun_pole1+nbun_pole2))*(j+0));												//�I�_�ʒu�v�Zx
		dry = naihan * sin((2.0*M_PI/360)*(45) + (2.0*M_PI/(nbun_pole1+nbun_pole2))*(j+0));												//�I�_�ʒu�v�Zy ���a
		drz = r_pole3;		//�I�_�ʒu�v�Zz
		//--�Z�O�����g�� �P�ʕ����x�N�g���̊e�����̌v�Z
		dcl = sqrt( pow( (rrx-drx),2 )
				  + pow( (rry-dry),2 )
				  + pow( (rrz-drz),2 ) );						//�Z�O�����g���v�Z
		ssx = (drx-rrx) / dcl;									//�P�ʃx�N�g��x
		ssy = (dry-rry) / dcl;									//�P�ʃx�N�g��y
		ssz = (drz-rrz) / dcl;									//�P�ʃx�N�g��z
		//--�v�Z���ʑ��
		RX[i] = rrx;											//�n�_�ʒux
		RY[i] = rry;											//�n�_�ʒuy
		RZ[i] = rrz;											//�n�_�ʒuz
		SX[i] = ssx;											//�P�ʃx�N�g��x
		SY[i] = ssy;											//�P�ʃx�N�g��y
		SZ[i] = ssz;											//�P�ʃx�N�g��z
		SEGL[i] = dcl;											//�Z�O�����g��
		i++;
	}


//------------------------------------------------�B�ۓ��f�q------------------------------------------------------------

	for(j = 0; j < nbun_pole3; ++j){
		//--�n�_ �I�_ �Z�O�����g���v�Z
		rrx = (naihan - ((j+0) * (r_pole2/nbun_pole3)))*cos((M_PI/180)*(45));										        //�n�_�ʒu�v�Zx
		rry = (naihan - ((j+0) * (r_pole2/nbun_pole3)))*sin((M_PI/180)*(45)); 												//�n�_�ʒu�v�Zy
		rrz = r_pole3;		//�n�_�ʒu�v�Zz
		drx = (naihan - ((j+1) * (r_pole2/nbun_pole3)))*cos((M_PI/180)*(45)); 												//�I�_�ʒu�v�Zx
		dry = (naihan - ((j+1) * (r_pole2/nbun_pole3)))*sin((M_PI/180)*(45));												//�I�_�ʒu�v�Zy
		drz = r_pole3;		//�I�_�ʒu�v�Zz
		//--�Z�O�����g�� �P�ʕ����x�N�g���̊e�����̌v�Z
		dcl = sqrt( pow( (rrx-drx),2 )
				  + pow( (rry-dry),2 )
				  + pow( (rrz-drz),2 ) );						//�Z�O�����g���v�Z
		ssx = (drx-rrx) / dcl;									//�P�ʃx�N�g��x
		ssy = (dry-rry) / dcl;									//�P�ʃx�N�g��y
		ssz = (drz-rrz) / dcl;									//�P�ʃx�N�g��z
		//--�v�Z���ʑ��
		RX[i] = rrx;											//�n�_�ʒux
		RY[i] = rry;											//�n�_�ʒuy
		RZ[i] = rrz;											//�n�_�ʒuz
		SX[i] = ssx;											//�P�ʃx�N�g��x
		SY[i] = ssy;											//�P�ʃx�N�g��y
		SZ[i] = ssz;											//�P�ʃx�N�g��z
		SEGL[i] = dcl;											//�Z�O�����g��
		i++;
	}


//------------------------------------------------�O�~(0~315)---------------------------------------------------------
	for(j = 0; j < nbun_pole1_2+1; ++j){
		//--�n�_ �I�_ �Z�O�����g���v�Z
		rrx = gaihan * cos((2.0*M_PI/360)*(22.5) + (2.0*M_PI/(nbun_pole1_2+nbun_pole2_2))*(j+0));	//�n�_�ʒu�v�Zx
		rry = gaihan * sin((2.0*M_PI/360)*(22.5) + (2.0*M_PI/(nbun_pole1_2+nbun_pole2_2))*(j+0));										//�n�_�ʒu�v�Zy
		rrz = r_pole3;																				//�n�_�ʒu�v�Zz
		drx = gaihan * cos((2.0*M_PI/360)*(22.5) + (2.0*M_PI/(nbun_pole1_2+nbun_pole2_2))*(j+1));										//�I�_�ʒu�v�Zx
		dry = gaihan * sin((2.0*M_PI/360)*(22.5) + (2.0*M_PI/(nbun_pole1_2+nbun_pole2_2))*(j+1));										//�I�_�ʒu�v�Zy
		drz = r_pole3;		//�I�_�ʒu�v�Zz
		//--�Z�O�����g�� �P�ʕ����x�N�g���̊e�����̌v�Z
		dcl = sqrt( pow( (rrx-drx),2 )
				  + pow( (rry-dry),2 )
				  + pow( (rrz-drz),2 ) );						//�Z�O�����g���v�Z
		ssx = (drx-rrx) / dcl;									//�P�ʃx�N�g��x
		ssy = (dry-rry) / dcl;									//�P�ʃx�N�g��y
		ssz = (drz-rrz) / dcl;									//�P�ʃx�N�g��z
		//--�v�Z���ʑ��
		RX[i] = rrx;											//�n�_�ʒux
		RY[i] = rry;											//�n�_�ʒuy
		RZ[i] = rrz;											//�n�_�ʒuz
		SX[i] = ssx;											//�P�ʃx�N�g��x
		SY[i] = ssy;											//�P�ʃx�N�g��y
		SZ[i] = ssz;											//�P�ʃx�N�g��z
		SEGL[i] = dcl;											//�Z�O�����g��
		i++;
	}

//------------------------------------------------�O�~(315~360)---------------------------------------------------------
	for(j = 0; j < nbun_pole2_2+1; ++j){
		//--�n�_ �I�_ �Z�O�����g���v�Z
		rrx = gaihan * cos((2.0*M_PI/360)*(-22.5) + (2.0*M_PI/(nbun_pole1_2+nbun_pole2_2))*(j+0));	//�n�_�ʒu�v�Zx
		rry = gaihan * sin((2.0*M_PI/360)*(-22.5) + (2.0*M_PI/(nbun_pole1_2+nbun_pole2_2))*(j+0));	//�n�_�ʒu�v�Zy
		rrz = r_pole3;																				//�n�_�ʒu�v�Zz
		drx = gaihan * cos((2.0*M_PI/360)*(-22.5) + (2.0*M_PI/(nbun_pole1_2+nbun_pole2_2))*(j+1));	//�I�_�ʒu�v�Zx
		dry = gaihan * sin((2.0*M_PI/360)*(-22.5) + (2.0*M_PI/(nbun_pole1_2+nbun_pole2_2))*(j+1));	//�I�_�ʒu�v�Zy
		drz = r_pole3;																				//�I�_�ʒu�v�Zz
		//--�Z�O�����g�� �P�ʕ����x�N�g���̊e�����̌v�Z
		dcl = sqrt( pow( (rrx-drx),2 )
				  + pow( (rry-dry),2 )
				  + pow( (rrz-drz),2 ) );						//�Z�O�����g���v�Z
		ssx = (drx-rrx) / dcl;									//�P�ʃx�N�g��x
		ssy = (dry-rry) / dcl;									//�P�ʃx�N�g��y
		ssz = (drz-rrz) / dcl;									//�P�ʃx�N�g��z
		//--�v�Z���ʑ��
		RX[i] = rrx;											//�n�_�ʒux
		RY[i] = rry;											//�n�_�ʒuy
		RZ[i] = rrz;											//�n�_�ʒuz
		SX[i] = ssx;											//�P�ʃx�N�g��x
		SY[i] = ssy;											//�P�ʃx�N�g��y
		SZ[i] = ssz;											//�P�ʃx�N�g��z
		SEGL[i] = dcl;											//�Z�O�����g��
		i++;
	}


	//------------------------------------------------�I�[�o�[���b�v:�O�ۓ��f�q------------------------------------------------------------
	for(j = 0; j < 1; ++j){
		//--�n�_ �I�_ �Z�O�����g���v�Z
		rrx = gaihan * cos((2.0*M_PI/360)*(22.5) + (2.0*M_PI/(nbun_pole1_2+nbun_pole2_2))*(j+1));												//�n�_�ʒu�v�Zx
		rry = gaihan * sin((2.0*M_PI/360)*(22.5) + (2.0*M_PI/(nbun_pole1_2+nbun_pole2_2))*(j+1));											//�n�_�ʒu�v�Zy ���a
		rrz = r_pole3;		//�n�_�ʒu�v�Zz
		drx = gaihan * cos((2.0*M_PI/360)*(22.5) + (2.0*M_PI/(nbun_pole1_2+nbun_pole2_2))*(j+0));												//�I�_�ʒu�v�Zx
		dry = gaihan * sin((2.0*M_PI/360)*(22.5) + (2.0*M_PI/(nbun_pole1_2+nbun_pole2_2))*(j+0));												//�I�_�ʒu�v�Zy ���a
		drz = r_pole3;		//�I�_�ʒu�v�Zz
		//--�Z�O�����g�� �P�ʕ����x�N�g���̊e�����̌v�Z
		dcl = sqrt( pow( (rrx-drx),2 )
				  + pow( (rry-dry),2 )
				  + pow( (rrz-drz),2 ) );						//�Z�O�����g���v�Z
		ssx = (drx-rrx) / dcl;									//�P�ʃx�N�g��x
		ssy = (dry-rry) / dcl;									//�P�ʃx�N�g��y
		ssz = (drz-rrz) / dcl;									//�P�ʃx�N�g��z
		//--�v�Z���ʑ��
		RX[i] = rrx;											//�n�_�ʒux
		RY[i] = rry;											//�n�_�ʒuy
		RZ[i] = rrz;											//�n�_�ʒuz
		SX[i] = ssx;											//�P�ʃx�N�g��x
		SY[i] = ssy;											//�P�ʃx�N�g��y
		SZ[i] = ssz;											//�P�ʃx�N�g��z
		SEGL[i] = dcl;											//�Z�O�����g��
		i++;
	}


//------------------------------------------------�O�ۓ��f�q------------------------------------------------------------

	for(j = 0; j < nbun_pole3_2; ++j){
		//--�n�_ �I�_ �Z�O�����g���v�Z
		rrx = (gaihan - ((j+0) * (r_pole2_2/nbun_pole3_2)))*cos((M_PI/180)*(22.5));										        //�n�_�ʒu�v�Zx
		rry = (gaihan - ((j+0) * (r_pole2_2/nbun_pole3_2)))*sin((M_PI/180)*(22.5)); 												//�n�_�ʒu�v�Zy
		rrz = r_pole3;		//�n�_�ʒu�v�Zz
		drx = (gaihan - ((j+1) * (r_pole2_2/nbun_pole3_2)))*cos((M_PI/180)*(22.5)); 												//�I�_�ʒu�v�Zx
		dry = (gaihan - ((j+1) * (r_pole2_2/nbun_pole3_2)))*sin((M_PI/180)*(22.5));												//�I�_�ʒu�v�Zy
		drz = r_pole3;		//�I�_�ʒu�v�Zz
		//--�Z�O�����g�� �P�ʕ����x�N�g���̊e�����̌v�Z
		dcl = sqrt( pow( (rrx-drx),2 )
				  + pow( (rry-dry),2 )
				  + pow( (rrz-drz),2 ) );						//�Z�O�����g���v�Z
		ssx = (drx-rrx) / dcl;									//�P�ʃx�N�g��x
		ssy = (dry-rry) / dcl;									//�P�ʃx�N�g��y
		ssz = (drz-rrz) / dcl;									//�P�ʃx�N�g��z
		//--�v�Z���ʑ��
		RX[i] = rrx;											//�n�_�ʒux
		RY[i] = rry;											//�n�_�ʒuy
		RZ[i] = rrz;											//�n�_�ʒuz
		SX[i] = ssx;											//�P�ʃx�N�g��x
		SY[i] = ssy;											//�P�ʃx�N�g��y
		SZ[i] = ssz;											//�P�ʃx�N�g��z
		SEGL[i] = dcl;											//�Z�O�����g��
		i++;
	}


//------------------------------------------------�I���˔�------------------------------------------------------------

	for(j = 0; j<nbun_pole1+nbun_pole2+nbun_pole3+1+1+1+nbun_pole1_2+nbun_pole2_2+nbun_pole3_2+1+1+1; ++j){
		//--�v�Z���ʑ��
		RX[i] = RX[j];											//�n�_�ʒux
		RY[i] = RY[j];											//�n�_�ʒuy
		RZ[i] = (-1.0)*RZ[j];									//�n�_�ʒuz
		SX[i] = SX[j];											//�P�ʃx�N�g��x
		SY[i] = SY[j];											//�P�ʃx�N�g��y
		SZ[i] = (-1.0)*SZ[j];									//�P�ʃx�N�g��z
		SEGL[i] = SEGL[j];										//�Z�O�����g��
		i++;
	}


//------------------------------------------------���~�I�[�o�[���b�v:���d�_(-z)------------------------------------------------------------
	for(j = 0; j < 1; ++j){
		//--�n�_ �I�_ �Z�O�����g���v�Z
		rrx = naihan * cos((2.0*M_PI/360)*(0) + (2.0*M_PI/(nbun_pole1+nbun_pole2))*(j+1));			//�n�_�ʒu�v�Zx
		rry = naihan * sin((2.0*M_PI/360)*(0) + (2.0*M_PI/(nbun_pole1+nbun_pole2))*(j+1));			//�n�_�ʒu�v�Zy ���a
		rrz = -r_pole3;																			//�n�_�ʒu�v�Zz
		drx = naihan * cos((2.0*M_PI/360)*(0) + (2.0*M_PI/(nbun_pole1+nbun_pole2))*(j+0));			//�I�_�ʒu�v�Zx
		dry = naihan * sin((2.0*M_PI/360)*(0) + (2.0*M_PI/(nbun_pole1+nbun_pole2))*(j+0));			//�I�_�ʒu�v�Zy ���a
		drz = -r_pole3;		//�I�_�ʒu�v�Zz
		//--�Z�O�����g�� �P�ʕ����x�N�g���̊e�����̌v�Z
		dcl = sqrt( pow( (rrx-drx),2 )
				  + pow( (rry-dry),2 )
				  + pow( (rrz-drz),2 ) );						//�Z�O�����g���v�Z
		ssx = (drx-rrx) / dcl;									//�P�ʃx�N�g��x
		ssy = (dry-rry) / dcl;									//�P�ʃx�N�g��y
		ssz = (drz-rrz) / dcl;									//�P�ʃx�N�g��z
		//--�v�Z���ʑ��
		RX[i] = rrx;											//�n�_�ʒux
		RY[i] = rry;											//�n�_�ʒuy
		RZ[i] = rrz;											//�n�_�ʒuz
		SX[i] = ssx;											//�P�ʃx�N�g��x
		SY[i] = ssy;											//�P�ʃx�N�g��y
		SZ[i] = ssz;											//�P�ʃx�N�g��z
		SEGL[i] = dcl;
		i++;
	}

//------------------------------------------------���~���d�_------------------------------------------------------------

	for(j = 0; j < nbun_pole4*2; ++j){
		//--�n�_ �I�_ �Z�O�����g���v�Z
		rrx = naihan;												//�n�_�ʒu�v�Zx
		rry = 0.0;											//�n�_�ʒu�v�Zy ���a
		rrz = (-1.0)*(r_pole3) + (j+0)*(r_pole3/nbun_pole4);		//�n�_�ʒu�v�Zz
		drx = naihan;											//�I�_�ʒu�v�Zx
		dry = 0.0;												//�I�_�ʒu�v�Zy ���a
		drz = (-1.0)*(r_pole3) + (j+1)*(r_pole3/nbun_pole4);		//�I�_�ʒu�v�Zz
		//--�Z�O�����g�� �P�ʕ����x�N�g���̊e�����̌v�Z
		dcl = sqrt( pow( (rrx-drx),2 )
				  + pow( (rry-dry),2 )
				  + pow( (rrz-drz),2 ) );						//�Z�O�����g���v�Z
		ssx = (drx-rrx) / dcl;									//�P�ʃx�N�g��x
		ssy = (dry-rry) / dcl;									//�P�ʃx�N�g��y
		ssz = (drz-rrz) / dcl;									//�P�ʃx�N�g��z
		//--�v�Z���ʑ��
		RX[i] = rrx;											//�n�_�ʒux
		RY[i] = rry;											//�n�_�ʒuy
		RZ[i] = rrz;											//�n�_�ʒuz
		SX[i] = ssx;											//�P�ʃx�N�g��x
		SY[i] = ssy;											//�P�ʃx�N�g��y
		SZ[i] = ssz;											//�P�ʃx�N�g��z
		SEGL[i] = dcl;											//�Z�O�����g��
		i++;
	}
	

//------------------------------------------------���~�I�[�o�[���b�v:���d�_(+z)------------------------------------------------------------
	for(j = 0; j < 1; ++j){
		//--�n�_ �I�_ �Z�O�����g���v�Z
		rrx = naihan * cos((2.0*M_PI/360)*(0) + (2.0*M_PI/(nbun_pole1+nbun_pole2))*(j+0));			//�n�_�ʒu�v�Zx
		rry = naihan * sin((2.0*M_PI/360)*(0) + (2.0*M_PI/(nbun_pole1+nbun_pole2))*(j+0));			//�n�_�ʒu�v�Zy ���a
		rrz = r_pole3;																			//�n�_�ʒu�v�Zz
		drx = naihan * cos((2.0*M_PI/360)*(0) + (2.0*M_PI/(nbun_pole1+nbun_pole2))*(j+1));			//�I�_�ʒu�v�Zx
		dry = naihan * sin((2.0*M_PI/360)*(0) + (2.0*M_PI/(nbun_pole1+nbun_pole2))*(j+1));			//�I�_�ʒu�v�Zy ���a
		drz = r_pole3;		//�I�_�ʒu�v�Zz
		//--�Z�O�����g�� �P�ʕ����x�N�g���̊e�����̌v�Z
		dcl = sqrt( pow( (rrx-drx),2 )
				  + pow( (rry-dry),2 )
				  + pow( (rrz-drz),2 ) );						//�Z�O�����g���v�Z
		ssx = (drx-rrx) / dcl;									//�P�ʃx�N�g��x
		ssy = (dry-rry) / dcl;									//�P�ʃx�N�g��y
		ssz = (drz-rrz) / dcl;									//�P�ʃx�N�g��z
		//--�v�Z���ʑ��
		RX[i] = rrx;											//�n�_�ʒux
		RY[i] = rry;											//�n�_�ʒuy
		RZ[i] = rrz;											//�n�_�ʒuz
		SX[i] = ssx;											//�P�ʃx�N�g��x
		SY[i] = ssy;											//�P�ʃx�N�g��y
		SZ[i] = ssz;											//�P�ʃx�N�g��z
		SEGL[i] = dcl;
		i++;
	}



	//------------------------------------------------�O�~�I�[�o�[���b�v:���d�_(-z)------------------------------------------------------------
	for(j = 0; j < 1; ++j){
		//--�n�_ �I�_ �Z�O�����g���v�Z
		rrx = gaihan * cos((2.0*M_PI/360)*(0) + (2.0*M_PI/(nbun_pole1_2+nbun_pole2_2))*(j+1));		//�n�_�ʒu�v�Zx
		rry = gaihan * sin((2.0*M_PI/360)*(0) + (2.0*M_PI/(nbun_pole1_2+nbun_pole2_2))*(j+1));		//�n�_�ʒu�v�Zy ���a
		rrz = -r_pole3;																	//�n�_�ʒu�v�Zz
		drx = gaihan * cos((2.0*M_PI/360)*(0) + (2.0*M_PI/(nbun_pole1_2+nbun_pole2_2))*(j+0));		//�I�_�ʒu�v�Zx
		dry = gaihan * sin((2.0*M_PI/360)*(0) + (2.0*M_PI/(nbun_pole1_2+nbun_pole2_2))*(j+0));		//�I�_�ʒu�v�Zy ���a
		drz = -r_pole3;																	//�I�_�ʒu�v�Zz
		//--�Z�O�����g�� �P�ʕ����x�N�g���̊e�����̌v�Z
		dcl = sqrt( pow( (rrx-drx),2 )
				  + pow( (rry-dry),2 )
				  + pow( (rrz-drz),2 ) );						//�Z�O�����g���v�Z
		ssx = (drx-rrx) / dcl;									//�P�ʃx�N�g��x
		ssy = (dry-rry) / dcl;									//�P�ʃx�N�g��y
		ssz = (drz-rrz) / dcl;									//�P�ʃx�N�g��z
		//--�v�Z���ʑ��
		RX[i] = rrx;											//�n�_�ʒux
		RY[i] = rry;											//�n�_�ʒuy
		RZ[i] = rrz;											//�n�_�ʒuz
		SX[i] = ssx;											//�P�ʃx�N�g��x
		SY[i] = ssy;											//�P�ʃx�N�g��y
		SZ[i] = ssz;											//�P�ʃx�N�g��z
		SEGL[i] = dcl;
		i++;
	}

//------------------------------------------------�O�~���d�_------------------------------------------------------------

	for(j = 0; j < nbun_pole4*2; ++j){
		//--�n�_ �I�_ �Z�O�����g���v�Z
		rrx = gaihan;												//�n�_�ʒu�v�Zx
		rry = 0.0;													//�n�_�ʒu�v�Zy ���a
		rrz = (-1.0)*(r_pole3) + (j+0)*(r_pole3/nbun_pole4);		//�n�_�ʒu�v�Zz
		drx = gaihan;												//�I�_�ʒu�v�Zx
		dry = 0.0;													//�I�_�ʒu�v�Zy ���a
		drz = (-1.0)*(r_pole3) + (j+1)*(r_pole3/nbun_pole4);		//�I�_�ʒu�v�Zz
		//--�Z�O�����g�� �P�ʕ����x�N�g���̊e�����̌v�Z
		dcl = sqrt( pow( (rrx-drx),2 )
				  + pow( (rry-dry),2 )
				  + pow( (rrz-drz),2 ) );						//�Z�O�����g���v�Z
		ssx = (drx-rrx) / dcl;									//�P�ʃx�N�g��x
		ssy = (dry-rry) / dcl;									//�P�ʃx�N�g��y
		ssz = (drz-rrz) / dcl;									//�P�ʃx�N�g��z
		//--�v�Z���ʑ��
		RX[i] = rrx;											//�n�_�ʒux
		RY[i] = rry;											//�n�_�ʒuy
		RZ[i] = rrz;											//�n�_�ʒuz
		SX[i] = ssx;											//�P�ʃx�N�g��x
		SY[i] = ssy;											//�P�ʃx�N�g��y
		SZ[i] = ssz;											//�P�ʃx�N�g��z
		SEGL[i] = dcl;											//�Z�O�����g��
		i++;
	}
	

//------------------------------------------------�O�~�I�[�o�[���b�v:���d�_(+z)------------------------------------------------------------
	for(j = 0; j < 1; ++j){
		//--�n�_ �I�_ �Z�O�����g���v�Z
		rrx = gaihan * cos((2.0*M_PI/360)*(0) + (2.0*M_PI/(nbun_pole1_2+nbun_pole2_2))*(j+0));	//�n�_�ʒu�v�Zx
		rry = gaihan * sin((2.0*M_PI/360)*(0) + (2.0*M_PI/(nbun_pole1_2+nbun_pole2_2))*(j+0));	//�n�_�ʒu�v�Zy ���a
		rrz = r_pole3;																		//�n�_�ʒu�v�Zz
		drx = gaihan * cos((2.0*M_PI/360)*(0) + (2.0*M_PI/(nbun_pole1_2+nbun_pole2_2))*(j+1));	//�I�_�ʒu�v�Zx
		dry = gaihan * sin((2.0*M_PI/360)*(0) + (2.0*M_PI/(nbun_pole1_2+nbun_pole2_2))*(j+1));	//�I�_�ʒu�v�Zy ���a
		drz = r_pole3;																		//�I�_�ʒu�v�Zz
		//--�Z�O�����g�� �P�ʕ����x�N�g���̊e�����̌v�Z
		dcl = sqrt( pow( (rrx-drx),2 )
				  + pow( (rry-dry),2 )
				  + pow( (rrz-drz),2 ) );						//�Z�O�����g���v�Z
		ssx = (drx-rrx) / dcl;									//�P�ʃx�N�g��x
		ssy = (dry-rry) / dcl;									//�P�ʃx�N�g��y
		ssz = (drz-rrz) / dcl;									//�P�ʃx�N�g��z
		//--�v�Z���ʑ��
		RX[i] = rrx;											//�n�_�ʒux
		RY[i] = rry;											//�n�_�ʒuy
		RZ[i] = rrz;											//�n�_�ʒuz
		SX[i] = ssx;											//�P�ʃx�N�g��x
		SY[i] = ssy;											//�P�ʃx�N�g��y
		SZ[i] = ssz;											//�P�ʃx�N�g��z
		SEGL[i] = dcl;
		i++;
	}

//--------------------------------------------------------------------------------------------------------------------
	//========================================================
	//			�e�Z�O�����g�̃��C���[���a����	�P�ʁF(m)
	//			RA[ ]		���C���[���a
	//========================================================
	for(i = 0; i < NSEG; ++i){
		RA[i] = wire_radius;	
	}

	//========================================================
	//			�e�G�������g(���C���[)���̃Z�O�����g��
	//			SEGN[ ]
	//========================================================
	
	//�@���@�I�[�o�[���b�v���݂Ł@��
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
	//			���d�֌W�ݒ�
	//			���d�ʒu		FEDP[ ]
	//			���d�d��		FEDV[ ]
	//
	//			���ʒu  FEDP[ ]
	//					[���d�������ʒu]-[���d���������C���[(���Ԗ�)]
	//			���d��  FEDV[ ]
	//				�@��P���d�̓d��
	//					�s���t���d��p����ꍇ   -2�~(1+j0)[V]
	//					���t���d��p����ꍇ     -1�~(1+j0)[V]
	//				�A���˔t���_�C�|�[����(���˔t�����t���d�A���e�i)
	//					��P���d(���˔\��)   -1�~(1+j0)[V]
	//					��Q���d(���˔���)    1�~(1+j0)[V]
	//						(���˔̕\�Ɨ��ŋ��d�ʑ����t�ɂ���)
	//				�B��P���d���C���[�W�@�̏ꍇ
	//					���̋��d�_���C���[�W�@��K�p����D
	//				�C��P���d���C���[�W�@��p���Ȃ��ꍇ
	//					���̋��d�_���C���[�W�@��p���Ȃ��D
	//				�D�������d�̓d���E�ʑ�������
	//					��P���d�͏����@�A��K�p
	//					��P���d�ȊO�Ő�����s���D
	//========================================================
	FEDP[0] = SEGN[0]+SEGN[1]+SEGN[2]+SEGN[3]+SEGN[4]+SEGN[5]+SEGN[6]+SEGN[7]+SEGN[8]+SEGN[9]+SEGN[10]+SEGN[11]-12+(SEGN[12]-2)/2+1-1;
	FEDP[1] = SEGN[0]+SEGN[1]+SEGN[2]+SEGN[3]+SEGN[4]+SEGN[5]+SEGN[6]+SEGN[7]+SEGN[8]+SEGN[9]+SEGN[10]+SEGN[11]+SEGN[12]-14+(SEGN[13]-2)/2+1-1+1;
	FEDV[0] = -2.0 * Complex( 1.0 , 0.0 );
	FEDV[1] = -2.0 * Complex( 0.70710678118 , -0.70710678118 );

	//========================================================
	//			�C���s�[�_���X���׊֌W�ݒ�
	//			���׈ʒu		LOADP[ ]
	//			���גl�@		LOADZ[ ]
	//
	//			���ʒu    LOADP[ ]
	//					[���ׂ������ʒu]-[���ׂ��������C���[(���Ԗ�)]
	//			�����גl�@LOADZ[ ]  (50����ڑ�����ꍇ)
	//				�@���˔ɒ�R��t����ꍇ		 -2�~(50+j0)[��]
	//				�A���C���̓r���ɒ�R��t����ꍇ -1�~(50+j0)[��]
	//				�B�ڑ��Ώۂɂ�炸�C�l�́u�}�C�i�X(-)�v�ɂȂ�
	//								(��R�l�̓x�N�g���ł͖�������)
	//========================================================


	//========================================================
	//			�e�Z�O�����g����̕��ˏ�Ԃ�ݒ�(�������ːݒ�)
	//			RAD_MODE[ ] = 1 or 0
	//				(0 : ���˃J�b�g   1 : �ʏ�̕���)
	//			�������őS��RAD_MODE[ ]=1 �ɐݒ�ς�
	//========================================================


	//========================================================
	//			�d���E���ˊE�v�Z
	//========================================================	
	ConfCheck();				//�`�󌟍�
	MakeZmn();					//Zmn�쐬
	MakeCurrent();				//�d���v�Z
	MakePhase();				//�d���ʑ��v�Z
	Radiation();				//���ˊE�v�Z
	LapsedTime();				//�o�ߎ��Ԏ擾

	//========================================================
	//			�f�[�^�o��
	//========================================================	
	OutputConf();				//�`��o��
	OutputCurrent();			//�d���o��
	OutputRad();				//���ˊE�o��
	OutputChara();				//�����f�[�^�o��


	//========================================================
	//			�z��̊J��
	//========================================================	
	DelMatAll();				//�z��J��(���R�����g�A�E�g�֎~��)
}

}
}
}
}
}
//============================================================================
//					�ϐ��Ɣz��ꗗ
//============================================================================
//
//--�`�� ���d
//		double	FREQ0					�݌v���g��f0
//		double	RAMDA0					�݌v���g���̎��R��Ԕg��
//		double	USEF					���d���g��
//		int		NWIR					�S���C���[��
//		int		NSEG					�S�Z�O�����g��
//		int		NFED					�S���d�_��
//		int		NSEG0					�S�d���v�Z�_��
//		int		NLOAD					��R�����א�
//--���ˊE�v�Z
//		int		AXMODE   				(0=�ӌŒ�, 1=�ƌŒ�)	
//		double	DegDelta 				���ݕ�
//		double	DegStart 				�����p
//		double	DegWidth 				�͈�
//		double	FixAngle 				�Œ莲�p�x
//--���ԑ���
//		int		la_min	la_sec			�� �b
//--�v�Z�񂵗p�p�����[�^
//		double	PARA1,PARA2				�p�����[�^�@�ƇA
//--�`��z��
//		double	RX[ ]  RY[ ]  RZ[ ]		�e�Z�O�����g�̎n�_
//		double�@SX[ ]  SY[ ]  SZ[ ]		�P�ʃx�N�g���̐���
//		double	SEGL[ ]	RA[ ]			�e�Z�O�����g�̒��� ���a�@		
//		int�@	SEGN[ ]					�e���C���[�̃Z�O�����g��
//		int		FEDP[ ]					�e���d�ʒu
//		complex	FEDV[ ]					�e���d�d��
//		int		RAD_MODE[ ]				�e�Z�O�����g�̕��˃��[�h
//		int		LOADP[ ]				�e�C���s�[�_���X���׈ʒu
//		complex LOADZ[ ]				�e�C���s�[�_���X���גl
//--�d���z��
//		complex Zmn[ ][ ]				�C���s�[�_���X�s��	
//		complex Im[ ]					�d�����z
//		double  PhaseIm[ ]				�d���̈ʑ�
//--���̓C���s�[�_���X
//		complex Zin[ ]					�e���d�_�̓��̓C���s�[�_���X
//		double  VSWR_50[ ]  VSWR_75[ ]	�e���d�_��50����75���ɑ΂���VSWR
//--���ˊE�z��
//		complex TRAD[ ] FRAD[ ]			E�Ƃ�E�ӂ̕��ˊE
//		complex RRAD[ ] LRAD[ ]			ER ��EL �̕��ˊE
//		double TPHASE[ ] FPHASE[ ]		E�Ƃ�E�ӂ̈ʑ�
//		double RPHASE[ ] LPHASE[ ]		ER ��EL �̈ʑ�
//		double TGAI[ ] FGAI[ ]			E�Ƃ�E�ӂ̗���
//		double TFGAI[ ]					E�Ƃ�E�ӂ̍��v�̗���
//		double RLGAI[ ]					ER ��EL �̍��v�̗���
//		double RGAI[ ] LGAI[ ]			ER ��EL �̗���
//		double TPAT[ ] FPAT[ ]			E�Ƃ�E�ӂ̃p�^�[��
//		double RPAT[ ] LPAT[ ]			ER ��EL �̃p�^�[��
//		double AR[ ]					����
//--��{�����萔
//		double PI						��
//		double C						����
//		double e0						�^�󒆂̓�������0
//		double u0						�^�󒆂̗U�d����0
//		double R						1.0 �Œ�
//--���ȗ��p
//		complex J						�����P�ʁ@J=��-1
//--�ϕ��p
//		int GaussTenNo					�K�E�X�ϕ����_  [ 4�Œ�]�i�ʏ�p�j
//		int GaussTenSpe					�K�E�X�ϕ����_��[40�Œ�]�i���ٓ_�p�j
//--�v�Z�p
//		double k0						k0
//		complex uair					u(air)
//		double Beta;					��
//============================================================================