% Daniel Sun 21020109 written for GNU octave

function price = Octane_menu()
	options = { "Regular 87"; "Medium 89"; "Premium 91"; "High Octane 94"; "Diesel" };
	type = menu("Chose a type", options);

	switch (type)
		case 1
			price = 100.1;
		case 2
			price = 107.5;
		case 3
			price = 112.3;
		case 4
			price = 115.3;
		case 5
			price = 106.9;
		otherwise
			error("please select an option!");
	end
end
