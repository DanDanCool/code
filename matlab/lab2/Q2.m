% written for GNU octave, octave lacks yyaxis
function [] = Q2()
	fset = { (@(x) (sin(x))) (@(x) (cos(x))) (@(x) (2 .* sin(x) .* cos(x))) (@(x) (sin(x) ./ cos(x))) };
	label = { "sin(x)"; "cos(x)"; "2sin(x)cos(x)"; "sin(x)/cos(x)" };
	x = linspace(0, 2*pi, 64);
	dim = { 2, 1 };
	for i = 1:2
		subplot(dim{:}, i);
		args = { x; fset{-1 + 2 * i}(x); x; fset{2 * i}(x); (@(x, y) (plot(x, y, "k-+"))); (@(x, y) (plot(x, y, "k-.")))};
		plotyy(args{:});
		xlabel("x (between 0 and 2pi)");
		indices = [1, 2] + (2 * (i - 1));
		legend(label{indices});
		hold off;
	end
end
