% written for GNU Octave
function [] = Q1a(b)
	f = @(x, y) (log(y + sin(x)));
	x = linspace(0, 15, 50);
	fxy = f(x, b);
	plot(x, fxy);
	title(sprintf("f(x, %.01f) vs x", b));
	xlabel("x");
	ylabel(sprintf("f(x, %.01f)", b));
end
