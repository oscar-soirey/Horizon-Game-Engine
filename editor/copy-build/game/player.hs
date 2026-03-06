/*
	le but de ce fichier est d'illustrer un langage de programmation
	propre a mon futur moteur de jeux
	le but du langage est d'etre le plus simple et le plus correct possible
	a utiliser tout en accordant de la sécurité et de la polyvalence.
	Ce code n'est pas réprésentatif et a surtout pour but de montrer la plupart
	des possibilités du langage : le HorizonScript (.hs)
*/

#include gametypes.hd

//classe Player héritée de la classe Character
//le parser résout automatiquement la classe parente et trouve ses symboles
//qu'elle vienne d'un dll du jeu compilé ou d'un autre fichier .hs
<Player : Character>

//types : int (32), int64, float, string, bool, index (alias int), char
//list<type>, map<key, value>, pair<key, value>
//donc une map c'est juste une liste de pair
//acceder a la key d'une pair : pair.first, et pair.second pour la value

int Life = 100;

list<int> Children;

void StartGame
	//i :  pair<index, int>
	//interdiction de supprimer les éléments dans une boucle
	auto it = for_each(Children)
		hprint it.first;
		Life--;
	end;
end;

void Jump
	this.velocity.y = 100.0;

	//index for_loop( first index, last index(compris) )
	index i = for_loop(0, 5)
	//pas besoin de parenthese quand il y a un seul argument
		hprint i;
	end;
	//result : 0\n1\n2\n3\n4\n5\n
end;

void JumpCustom(int Force, string fallback)
	//code ici
end;

//manipuler des listes
list<int>;
list.add int;
list.remove_index index;
list.find object;  //retourne une liste de <index>
list.append list<object>;

//manipuler des maps (keys uniques)
map<string, int>
map.add("key", 0);
map.remove "key";
map.find object;  //retourne la clée de l'object

//traduction :
key "hello";  //return si il trouve la clée traduite dans la langue cible

index first = for_loop(1, 100)
	index second = for_loop(1,100)
		hprint(format("bonjour indexes : {first}, {second}"));
	end;
end;
