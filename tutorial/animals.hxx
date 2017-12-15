#ifndef animals_hxx
#define animals_hxx

/*
   - ara afegim un nou atribut a la base de tipus std::string
   - afegim accessors d'escriptura i de lectura
 */

#include <iostream>
#include <string>
#include <list>


class Animal
{
public:
	virtual void escriuEspecie() const
	{
		std::cout << "...indefinida..." << std::endl;
	}
	void nom(std::string elNom)
	{
		_nom = elNom;
	}
	std::string& nom()
	{
		return _nom;
	}
	virtual void amigo(Animal*nuevoamigo)
	{
		Amigos.push_back(nuevoamigo);		
	}
	
	std::list<Animal*> mostrar_amigos()
	{
		return Amigos;
	}	

private:
	std::string _nom;
	std::list<Animal*> Amigos;

};

class Elefant : public Animal
{
public:
	virtual void escriuEspecie() const
	{
		std::cout << "elefant" << std::endl;
	}
};

class Granota : public Animal
{
public:
	virtual void escriuEspecie() const
	{
		std::cout << "granota" << std::endl;
	}
};

class Gat : public Animal
{
public:
	virtual void escriuEspecie() const
	{
		std::cout << "gat" << std::endl;
	}
};

#endif
