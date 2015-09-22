require "prime"

def num(x)
  Prime.prime_division(x).inject(1) { |s, x| s * (x[1] + 1) }
end

n = gets.to_i
puts (1..10000).find { |x| num(x) == n }
