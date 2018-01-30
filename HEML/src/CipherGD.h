#ifndef CIPHERGD_H_
#define CIPHERGD_H_

#include <Scheme.h>
#include <SecretKey.h>

using namespace NTL;

class CipherGD {
public:
	Scheme& scheme;
	SecretKey& secretKey;

	double degree3[3] = {-0.5,0.15012,-0.001593};
	double degree5[4] = {-0.5,0.19131,-0.0045963, 0.0000412332};
	double degree7[5] = {-0.5,0.216884,-0.00819276,0.000165861,-0.00000119581};

//	double degree3[3] = {-0.5,0.19,-0.0035};
//	double degree5[4] = {-0.5,0.2166,-0.0077,0.00011};
//	double degree7[5] = {-0.5,0.216884,-0.00819276,0.000165861,-0.00000119581};

	CipherGD(Scheme& scheme, SecretKey& secretKey) : scheme(scheme), secretKey(secretKey) {}

	void encxyData(Ciphertext* cxyData, double** xyData, long slots, long factorDim, long learnDim, long batch, long cnum, long wBits);

	void encwData(Ciphertext* cwData, Ciphertext* cxyData, long cnum, long sBits, long bBits);

	ZZX generateAuxPoly(long slots, long batch, long pBits);

	Ciphertext encIP(Ciphertext* cxyData, Ciphertext* cwData, ZZX& poly, long cnum, long bBits, long wBits);

	void encSigmoid(long approxDeg, Ciphertext* cxyData, Ciphertext* cgrad, Ciphertext& cip, long cnum, double gamma, long sBits, long bBits, long wBits, long aBits);

	void encLGDstep(Ciphertext* cwData, Ciphertext* cgrad, long cnum);
	void encMLGDstep(Ciphertext* cwData, Ciphertext* cvData, Ciphertext* cgrad, double eta, long cnum, long wBits);
	void encNLGDstep(Ciphertext* cwData, Ciphertext* cvData, Ciphertext* cgrad, double eta, long cnum, long pBits);

	void encLGDiteration(long approxDeg, Ciphertext* cxyData, Ciphertext* cwData, ZZX& poly, long cnum, double gamma, long sBits, long bBits, long wBits, long aBits);
	void encMLGDiteration(long approxDeg, Ciphertext* cxyData, Ciphertext* cwData, Ciphertext* cvData, ZZX& poly, long cnum, double gamma, double eta, long sBits, long bBits, long wBits, long aBits);
	void encNLGDiteration(long approxDeg, Ciphertext* cxyData, Ciphertext* cwData, Ciphertext* cvData, ZZX& poly, long cnum, double gamma, double eta, long sBits, long bBits, long wBits, long pBits, long aBits);

	void decwData(double* wData, Ciphertext* cwData, long factorDim, long batch, long cnum, long wBits);
};

#endif /* CIPHERGD_H_ */
