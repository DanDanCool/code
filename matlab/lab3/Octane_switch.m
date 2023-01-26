% Daniel Sun 21020109 written for GNU octave

function price = Octane_switch(type)
	switch (type)
		case { "Regular"; 87 }
			price = 100.1;
		case { "Medium"; 89 }
			price = 107.5;
		case { "Premium"; 91 }
			price = 112.3;
		case { "High Octane"; 94 }
			price = 115.3;
		case { "Diesel" }
			price = 106.9;
		otherwise
			error("Unknown fuel type!");
	end
end
