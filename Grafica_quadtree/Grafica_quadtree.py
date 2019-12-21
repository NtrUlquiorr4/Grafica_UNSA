from PIL import Image, ImageDraw
from colormath.color_objects import LabColor, sRGBColor
from colormath.color_conversions import convert_color
from colormath.color_diff import delta_e_cie2000
from math import floor, ceil
from enum import Enum

class Color(Enum): #catalogar el color del objeto a ser dividido
	mixto = 1 #valor del color del objeto
	no_esta_determinado = 2 #valor del color sin determinar

class Rect:
	def __init__(self, x_i, y_i, x_f, y_f): #constructor
		self.x_i = x_i #para definir el constructor brindamos los 6 datos correspondientes
		self.y_i = y_i
		self.x_f = x_f
		self.y_f = y_f
		self.color = Color.no_esta_determinado #el objeto no posee color determinado
		self.divisiones = None #al inicio no existen divisiones
	def draw(self, image):	#dibujar la division del quadtree 
		if self.divisiones is None: #cuando no hay divisiones comienza la division del quadtree
			image = ImageDraw.Draw(image)
			image.rectangle([self.x_i, self.y_i, self.x_f, self.y_f],outline="yellow") #el color vario para cada prueba realizada
		else:
			for r in self.divisiones: 
				r.draw(image)
	def __str__(self):
		color_real = None #definiendo el color de la imagen
		if self.color is Color.mixto 				: color_real = "mixto" #definir color mixto o no determinado
		elif self.color is Color.no_esta_determinado	: color_real = "No esta determinado"
		else									: color_real = self.color
		return f"{self.x_i}, {self.y_i}, {self.x_f}, {self.y_f} \nColor: {color_real}" #devolver los coleres reales

def obtener_diff(primer_color, segundo_color):
	color1 = sRGBColor(primer_color[0], primer_color[1], primer_color[2])
	color2 = sRGBColor(segundo_color[0], segundo_color[1], segundo_color[2])
	color1 = convert_color(color1, LabColor); #convertir color 1
	color2 = convert_color(color2, LabColor); #convertir color 2
	delta_e = delta_e_cie2000(color1, color2)
	return delta_e

def obtener_color_diff(image, rect): 
	pixel = image.getpixel((rect.x_i, rect.y_i)) #obteniendo los pixeles del objeto
	for i in range(rect.x_i, rect.x_f):
		for j in range(rect.y_i, rect.y_f):
			diff = obtener_diff(pixel, image.getpixel((i, j))) #definiendo diff como pixel del objeto
			pixel = image.getpixel((i, j)) #actualizando pixel y diff en cada iteracion
			if diff >= 6: return (True, Color.mixto) #definiendo el color mixto con el parametro establecido
	return (False, pixel)

def hacer_division(image, rect):
	obtener_diff, color = obtener_color_diff(image, rect) #obteniendo color para la division en el quadtree
	if obtener_diff:
		rect.color = Color.mixto
		x_i, y_i, x_f, y_f = (rect.x_i, rect.y_i, rect.x_f, rect.y_f)
		x_mid, y_mid = floor((x_f-x_i)/2.0), floor((y_f-y_i)/2.0)
		div1 = Rect(x_i, y_i, x_i+x_mid, y_i+y_mid) #primera division
		div2 = Rect(x_i+x_mid, y_i, x_f, y_i+y_mid) #segunda division
		div3 = Rect(x_i, y_i+y_mid, x_i+x_mid, y_f) #tercera division
		div4 = Rect(x_i+x_mid, y_i+y_mid, x_f, y_f) #cuarta division
		rect.divisiones = [div1, div2, div3, div4]
		for r in rect.divisiones:
			hacer_division(image, r) #haciendo las divisiones de forma iterativa
	else:
		rect.color = color

image = Image.open("stitch.jpg")
rgb_image = image.convert('RGB')
width, height = rgb_image.size
quadtree = Rect(0, 0, width, height)
hacer_division(rgb_image, quadtree)
quadtree.draw(rgb_image)
rgb_image.show()
