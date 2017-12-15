/* 
   - usem els accessors d'escriptura i de lectura de l'atribut _nom

   En resum hem après:
   - com escriure per consola fent servir <iostream>
   - simbols de la libreria localitzats al namespace std::
   - les classes acaben en ;
   - el mètodes i atributs per defecte són private
   - com fer subclasses: "Sub : public Super"
   - perquè serveixen els mètodes virtuals
   - polimorfisme
   - usar #ifndef als headers per evitar redefinicions
   - pas de paràmetres per referència
   - col.leccions estàndars vector i list
   - typdefs
   - iteradors
   - std::string
   - ús d'accessors

	it should be possible to visualize the friends of a given animal.
 */

#include <list>
#include "animals.hxx"

typedef std::list<Animal*> Animals;
typedef std::list<Animal*> Amigos;

int main(void)
{
	Animals animals;

	// introduïm un de cada tipus
	Animal unAnimal;
	unAnimal.nom("Pikatxu");
	animals.push_back(&unAnimal);

	Elefant unElefant;
	unElefant.nom("Jumbo l'Orellut");
	animals.push_back(&unElefant); 

	Granota unaGranota;
	unaGranota.nom("Gustavo el Reporter");
	animals.push_back(&unaGranota);

	Gat unGat;
	unGat.nom("Gat Amb Botes");
	animals.push_back(&unGat);
	
	Animals amigos;
	//friends:
	unGat.amigo(&unaGranota);
	unGat.amigo(&unAnimal);
	unGat.amigo(&unElefant);
	//show friends
	amigos = unGat.mostrar_amigos();

	// iterem fent servir iteradors
	for (Animals::iterator it=animals.begin(); it!=animals.end(); it++)
	{
		std::cout << "l'animal anomenat " << (*it)->nom() << " es de l'especie ";
		(*it)->escriuEspecie();
	}
		std::cout << "els amics de l'animal " << unGat.nom() << " son : " << std::endl;
		
	for (Amigos::iterator it=amigos.begin(); it!=amigos.end(); it++)
	{
		std::cout << (*it)->nom() << std::endl;
	}

	return 0;
}

