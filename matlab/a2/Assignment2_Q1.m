% Daniel Sun 21020109, written for GNU octave
function [] = Assignment2_Q1()
	x = [ +1 +1 +0 -1 -1 -1 +0 +1 +0 ]';
	y = [ +0 +1 +1 +1 +0 -1 -1 -1 +0 ]';
	s.x = x;
	s.y = y;
	[s.r, s.theta] = cart2polar(x, y);
	pretty_format(s)
end

% gnu octave lacks table functionality
function output = pretty_format(val)
	if exist('table')
		output = struct2table(val);
	else
		output = val;
	end
end

function [r, theta] = cart2polar(x, y)
	r = ((x .^ 2) + (y .^ 2)) .^ 0.5;
	% makes use of floating point division -> a/0 = pm inf
	theta = atan(y./x);

	% correct for case where x, y = 0
	theta(isnan(theta)) = 0;

	% correction for quadrants 2 and 3
	correction = 0 + (y >= 0 & x < 0) .* pi - (y < 0 & x < 0) .* pi;
	theta = theta + correction;
end
