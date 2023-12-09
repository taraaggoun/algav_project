import matplotlib.pyplot as plt

def get_dict(filename):
	data_dict = {}
	with open(filename, 'r') as file:
		for line in file:
			tokens = line.strip().split()
			func_name = tokens[0]
			size = int(tokens[1])
			time = float(tokens[2])
			if func_name in data_dict:
				sizes = [pair[0] for pair in data_dict[func_name] and size < 100000]
				if size not in sizes:
					data_dict[func_name].append([size, time])
			else:
				data_dict[func_name] = [[size, time]]
	return data_dict

def get_graph(data_dict, func_name):
	func = func_name
	if func_name in data_dict:
		sizes = [entry[0] for entry in data_dict[func]]
		times = [entry[1] for entry in data_dict[func]]
		plt.plot(sizes, times, '.', label=func)

def main():
	print("--------------------- Tas min sous forme d'arbre ---------------------\n")
	print("Creation du graphe pour l'ajout iteratif et la construction\n")
	data_dict = get_dict("graph/ressource/min_heap_tree")
	get_graph(data_dict, "mhtree_ajout_iteratifs")
	get_graph(data_dict, "mhtree_construction")
	plt.xlabel("Nombres de cles")
	plt.ylabel("Temps en ms")
	plt.title("Ajout et construction, min heap tree")
	plt.legend()
	plt.savefig("graph/ressource/mht_add-const.png")
	plt.show()
	plt.close()
	print("Creation du graphe pour l'union\n")
	get_graph(data_dict, "mhtree_union")
	plt.xlabel("Nombres de cles")
	plt.ylabel("Temps en ms")
	plt.savefig("graph/ressource/mht_union.png")
	plt.title("Union, min heap tree")
	plt.legend()
	plt.show()
	plt.close()
 
	print("--------------------- Tas min sous forme de tableau ---------------------\n")
	print("Creation du graphe pour l'ajout iteratif et la construction\n")
	data_dict = get_dict("graph/ressource/min_heap_array")
	get_graph(data_dict, "mharray_ajout_iteratif")
	get_graph(data_dict, "mharray_construction")
	plt.xlabel("Nombres de cles")
	plt.ylabel("Temps en ms")
	plt.title("Ajout et construction, min heap array")
	plt.legend()
	plt.savefig("graph/ressource/mha_add-const.png")
	plt.show()
	plt.close()
	print("Creation du graphe pour l'union\n")
	get_graph(data_dict, "mharray_union")
	plt.xlabel("Nombres de cles")
	plt.ylabel("Temps en ms")
	plt.savefig("graph/ressource/mha_union.png")
	plt.title("Union, min heap array")
	plt.legend()
	plt.show()
	plt.close()

	print("--------------------------------------------------------------------------")

if __name__ == "__main__":
    main()
