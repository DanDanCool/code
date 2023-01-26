% written for GNU octave
function [] = Q1c(b)
	x = linspace(0, 15, 50);
	fxy = f(x, b);
	plot(x, fxy);
	title(sprintf("f(x, %.01f) vs x", b));
	xlabel("x");
	ylabel(sprintf("f(x, %.01f)", b));
end
