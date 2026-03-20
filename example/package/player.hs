<Player : Character>

int sum_list(list nums)
	int result = 0;
	
	auto elem = for_each(nums)
		result = result + elem;
	end;
	
	return result;
end;

int main
list damages = {10, 5, 7, 12};

hprint("Damage values:");

auto d = for_each(damages)
	hprint(d);
end;

int total = sum_list(damages);
hprint("Total damage:", total);

map<string, int> players = {[ "Alice", 120 ], [ "Bob", 95 ]};

hprint("Players:");

auto p = for_each_map(players)
	hprint(p.first, "life:", p.second);
end;

players.add("Charlie", 150);

hprint("Updated players:");

auto p = for_each_map(players)
	hprint(p.first, "life:", p.second);
end;

end;

