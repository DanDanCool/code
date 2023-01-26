% written for GNU octave
function [] = Q1b()
	f = @(x, y) (log(y + sin(x)));
	x = linspace(0, 15, 50);
	b = [1 1.2 2];
	for i = b
		fxy = f(x, i);
		plot(x, fxy);
		hold on
	end
	title("f(x, b) vs x")
	xlabel("x")
	ylabel("f(x, b)")
	labels = cellstr(strsplit(sprintf("f(x, %0.1f)\n", b), '\n'));
	% extra cell at the end due to the trailing newline delimiter
	legend(labels{1:end-1})
	hold off
end
