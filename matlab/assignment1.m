%"d6sun 21020109"
function [] = assignment1()
	figure(1)
	i4 = futureworth(1000000, 0.04, 11);
	i8 = futureworth(1000000, 0.08, 11);

	plot(i4.year, i4.future_worth, "o--");
	hold on;
	plot(i8.year, i8.future_worth, "s--");
	title("Principal vs Year");
	xlabel("Year");
	ylabel("Principal");
	legend("interest = 4%", "interest = 8%");
	hold off;

	pretty_format(i4)
	pretty_format(annualpayment(55000, 0.066, 5))

	figure(2)
	myplot()
end

% gnu octave lacks table functionality
function output = pretty_format(val)
	if exist('table')
		output = struct2table(val);
	else
		output = val;
	end
end

function futures = futureworth(principal, interest, years)
	year = 0:years;
	future_worth = principal .* (1 + interest) .^ year;
	year = year';
	future_worth = future_worth';
	futures.year = year;
	futures.future_worth = future_worth;
end

function payments = annualpayment(principal, interest, years)
	year = 1:years;
	annual_payment = principal .* interest .* (1 + interest) .^ year;
	annual_payment = annual_payment ./ ((1 + interest) .^ year - 1);
	year = year';
	annual_payment = annual_payment';
	payments.year = year;
	payments.annual_payment = annual_payment;
end

function [] = myplot()
	f = inline("sin(x/2)");
	g = @(y) (2 * cos(y));

	x = 0:pi/8:4*pi;
	y = x;

	fx = f(x);
	gy = g(y);

	plot(x, fx, "o--");
	hold on;
	plot(y, gy, "s--");

	title("f(x) and g(y)");
	xlabel("x and y");
	ylabel("f(x) and g(y)");
	legend("f(x) = sin(x/2)", "g(y) = 2cos(y)");

	hold off;
end
