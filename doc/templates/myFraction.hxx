#ifndef myFraction_hxx
#define myFraction_hxx
template <class ElementType>
class myFraction{

private: 
	ElementType _a;
	ElementType _b;

public:
	myFraction(ElementType a, ElementType b)	//CONSTRUCTOR
	{
		ElementType m = MCD(a,b);
		_a = a/m;
		_b = b/m;
	}

	ElementType a() const { return _a; }	//Getter _a
	ElementType b() const { return _b; }	//Getter _b
	
	ElementType MCD(ElementType a, ElementType b)	//Método MCD
	{
		if (a%b==0) { return b; }
		else { MCD (b, a%b); }
	}

	myFraction<ElementType> operator+ (const myFraction & other) const	//Método suma
	{
		return myFraction (_a * other.b() + _b * other.a(), _b * other.b() );
	}

	myFraction<ElementType> operator* (const myFraction & other) const	//Método multiplicación
	{
		return myFraction (_a * other.a(), _b * other.b() );
	}	

};
#endif
