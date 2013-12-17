_ = require "underscore"

f = (x)->
  return 8 if x % 3 == 0 && x % 5 == 0
  return 4 if x % 3 == 0 || x % 5 == 0
  x.toString().length

sum = 0
_([1..1000]).each (x)->
  sum += f(x)
  console.log "#{x}:\t\t#{sum}"

