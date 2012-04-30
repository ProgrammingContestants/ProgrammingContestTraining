class Point
  def initialize(x, y)
    @x = x
    @y = y
  end
  def x; @x; end
  def y; @y; end
  def x=(x); @x = x; end
  def y=(y); @y = y; end

  def +(other)
    Point.new(self.x+other.x, self.y+other.y)
  end

  def -(other)
    Point.new(self.x-other.x, self.y-other.y)
  end

  def *(other)
    Point.new(self.x*other, self.y*other)
  end

  def /(other)
    Point.new(self.x/other, self.y/other)
  end

  def sqabs
    @x*@x + @y*@y
  end

  def abs
    Math.sqrt(@x**2 + @y**2)
  end

  def dot(other)
    self.x*other.x + self.y*other.y
  end

  def cross(other)
    self.x*other.y - self.y*other.x
  end

  def included_in?(p1, p2, p3)
    res1 = (self-p1).cross(p2-p1)
    res2 = (self-p2).cross(p3-p2)
    res3 = (self-p3).cross(p1-p3)

    return true if res1<=0 && res2<=0 && res3<=0
    return true if res1>=0 && res2>=0 && res3>=0

    false
  end

  def to_s; self.inspect; end

  def inspect
    "[x=#{@x}, y=#{@y}]"
  end
end

require 'pp'

EPS = 1e-7

def route(points)
  len = 0
  for from,to in points.each_cons(2)
    len += (to-from).abs
  end

  len
end

def min_route(points, pins)
  min = 0
  while true

    i = 0
    while i<points.size-2
      p1 = points[i]
      p2 = points[i+1]
      p3 = points[i+2]

      pin = nil
      min_theta = Math::PI

      for p in pins
        next if not p.included_in?(p1, p2, p3)
        vec1 = p2-p1
        vec2 = p-p1
        cos = vec1.dot(vec2)/Math::sqrt(vec1.sqabs*vec2.sqabs)
        cos = 1 if cos>1
        theta = Math.acos(cos)
        if theta<min_theta
          min_theta = theta
          pin = p
        end
      end

      # puts pin

      if pin.nil?
        points.delete p2
      else
        vec = p2-pin
        points.insert(i+1, pin+vec/vec.abs*EPS)
        i += 1
      end

    end

    new_route = route(points)
    if (min-new_route).abs<EPS
      min = new_route
      break
    else
      min = new_route
    end

  end

  min
end


while true
  m,n = gets.split.map(&:to_i)
  break if m==0 && n==0

  points =[]
  pins = []
  m.times do
    x,y = gets.split.map(&:to_i)
    points << Point.new(x,y)
  end

  n.times do
    x,y = gets.split.map(&:to_i)
    pins << Point.new(x,y)
  end

  ans = min_route(points, pins)
  puts ans

end



