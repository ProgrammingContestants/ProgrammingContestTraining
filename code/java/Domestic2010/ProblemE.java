package Domestic2010;

import java.io.InputStream;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class ProblemE {
	public static void main(String[] args) {
		new ProblemE().solve(System.in);
	}

	static class Vertex {
		public List<Edge> edges;
		public String state;

		public Vertex() {
			edges = new ArrayList<Edge>();
		}
	}

	static class Edge {
		public Vertex to;
		public String string;

		public Edge(Vertex vertex, String str) {
			super();
			this.to = vertex;
			this.string = str;
		}
	}

	private void solve(InputStream in) {
		Scanner sc = new Scanner(in);
		while (true) {
			int nVertex = sc.nextInt();
			int nEdge = sc.nextInt();
			int startVertex = sc.nextInt();
			int goalVertex = sc.nextInt();
			if (nVertex == 0) {
				break;
			}

			Vertex[] vertexes = new Vertex[nVertex];
			for (int i = 0; i < vertexes.length; i++) {
				vertexes[i] = new Vertex();
			}

			for (int i = 0; i < nEdge; i++) {
				int from = sc.nextInt();
				int to = sc.nextInt();
				vertexes[to].edges.add(new Edge(vertexes[from], sc.next()));
			}

			vertexes[goalVertex].state = "";
			String answer = bellmanFord(vertexes, startVertex);
			System.out.println(answer == null ? "NO" : answer);
		}
	}

	private String bellmanFord(Vertex[] vertexes, int goalVertex) {
		for (int i = 0; i < vertexes.length * 6; i++) {
			for (int j = 0; j < vertexes.length; j++) {
				String state = vertexes[j].state;
				if (state == null) {
					continue;
				}
				for (Edge edge : vertexes[j].edges) {
					String newState = edge.string + state;
					if (edge.to.state == null
							|| edge.to.state.compareTo(newState) > 0) {
						if (edge.to == vertexes[goalVertex]
								&& i >= vertexes.length) {
							return null;
						}
						edge.to.state = newState;
					}
				}
			}
		}
		return vertexes[goalVertex].state;
	}
}
