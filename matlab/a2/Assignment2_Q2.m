% Daniel Sun 21020109, written for GNU octave
function mat = Assignment2_Q2
	mat = zeros(3);
	for i = 1:3
		for j = 1:3
			val = (i ~= j) * (i + j);
			mat(i, j) = val;
		end
	end
end
