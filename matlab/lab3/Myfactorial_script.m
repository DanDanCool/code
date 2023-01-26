% Daniel Sun 21020109 written for GNU octave
function [] = Myfactorial_script()
	valid = { "yes"; "y"; "no"; "n" };
	n = 10;
	while 1
		in = input("would you like to provide a number? (y)es/(n)o: ", "s");
		yes = { "yes"; "y" };
		if sum(ismember(yes, in))
			while 1
				% note: for some reason this still evaluates expressions... whatever
				val = input("provide a number: ", "s");
				val = str2num(val);
				if (length(val) == 1) && (val(1) == uint64(val(1)))
					n = uint64(val(1));
					break;
				else
					% remove to continuously probe until valid input
					error("Input must be a positive scalar integer!");
				end
			end
		end

		if sum(ismember(valid, in))
			break
		end
	end

	builtinans = factorial(n);
	myans = myfactorial(n);

	disp(sprintf("The factorial for %u! from our method is %u", n, myans));
	disp(sprintf("The factorial for %u! from the buildin matlab function is %u", n, builtinans));
end

function out = myfactorial(n)
	% this function is limited to quadword precision
	out = 1;
	for i = 1:n
		out = out * i;
	end
end
