import matplotlib.pyplot as plt
import pylab

def get_dict(filename):
	data_dict = {}
	with open(filename, 'r') as file:
		for line in file:
			tokens = line.strip().split()
			func_name = tokens[0]
			size = int(tokens[1])
			time = float(tokens[2])
			if func_name in data_dict:
				sizes = [pair[0] for pair in data_dict[func_name]]
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
	plt.xlabel("Nombres de clés")
	plt.ylabel("Temps en ms")
	plt.title("Ajout et construction, min heap tree")
	plt.legend()
	plt.savefig("graph/ressource/mht_add-const.png")
	plt.show()
	plt.close()
	print("Creation du graphe pour l'union\n")
	get_graph(data_dict, "mhtree_union")
	plt.xlabel("Nombres de clés")
	plt.ylabel("Temps (ms)")
	plt.title("Union, min heap tree")
	plt.legend()
	plt.savefig("graph/ressource/mht_union.png")
	plt.show()
	plt.close()
 
	print("--------------------- Tas min sous forme de tableau ---------------------\n")
	print("Creation du graphe pour l'ajout iteratif et la construction\n")
	data_dict = get_dict("graph/ressource/min_heap_array")
	get_graph(data_dict, "mharray_ajout_iteratif")
	get_graph(data_dict, "mharray_construction")
	plt.xlabel("Nombres de clés")
	plt.ylabel("Temps en ms")
	plt.title("Ajout et construction, min heap array")
	plt.legend()
	plt.savefig("graph/ressource/mha_add-const.png")
	plt.show()
	plt.close()
	print("Creation du graphe pour l'union\n")
	get_graph(data_dict, "mharray_union")
	plt.xlabel("Nombres de clés")
	plt.ylabel("Temps (ms)")
	plt.title("Union, min heap array")
	plt.legend()
	plt.savefig("graph/ressource/mha_union.png")
	plt.show()
	plt.close()

	print("------------------------------ Shakespeare -----------------------------\n")
	data_dict = get_dict("graph/ressource/shakespeare")
	x = [1, 2, 3]
	y = [data_dict.get("mhtree_suppr_min", [[0, 0]])[0][1], data_dict.get("mharray_suppr_min", [[0, 0]])[0][1], data_dict.get("binomq_suppr_min", [[0, 0]])[0][1]]
	name = ["mhtree_suppr_min", "mharray_suppr_min", "binomq_suppr_min"]
	plt.bar(x,y)
	pylab.xticks(x, name)
	plt.savefig("graph/ressource/supp_min.png")
	plt.ylabel("Temps (ms)")
	plt.title("Suppression Min")
	plt.show()
	plt.close()

	get_graph(data_dict, "mhtree_ajout")
	get_graph(data_dict, "mharray_ajout")
	get_graph(data_dict, "binomq_ajout")
	plt.xlabel("Nombres de clés")
	plt.ylabel("Temps en ms")
	plt.title("Ajout")
	plt.legend()
	plt.savefig("graph/ressource/ajout.png")
	plt.show()
	plt.close()

	get_graph(data_dict, "mhtree_construction")
	get_graph(data_dict, "mharray_construction")
	get_graph(data_dict, "binomq_construction")
	plt.xlabel("Nombres de clés")
	plt.ylabel("Temps en ms")
	plt.title("Ajout")
	plt.legend()
	plt.savefig("graph/ressource/ajout.png")
	plt.show()
	plt.close()

	print("--------------------------------------------------------------------------")


if __name__ == "__main__":
    main()
