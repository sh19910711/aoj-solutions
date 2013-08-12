10000.times {
  list = Array.new(6)
  begin
    list[0] = rand(2**14) + 2 
    list[1] = rand(2**14) + 2 
  end while list[0].gcd(list[1]) != 1
  begin
    list[2] = rand(2**14) + 2 
    list[3] = rand(2**14) + 2 
  end while list[2].gcd(list[3]) != 1
  begin
    list[4] = rand(2**14) + 2 
    list[5] = rand(2**14) + 2 
  end while list[4].gcd(list[5]) != 1
  puts "#{list.join(' ')}\n"
}
puts "#{Array.new(6).map{|v| 0}.join(' ')}\n"
