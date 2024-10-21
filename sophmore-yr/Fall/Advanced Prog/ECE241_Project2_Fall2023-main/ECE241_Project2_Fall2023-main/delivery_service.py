"""
UMass ECE 241 - Advanced Programming
Project 2 - Fall 2023
"""
import sys
from graph import Graph, Vertex
from priority_queue import PriorityQueue

class DeliveryService:
    def __init__(self) -> None:
        """
        Constructor of the Delivery Service class
        """
        self.city_map = Graph()
        self.MST = Graph()

    def buildMap(self, filename: str) -> None:
        """
        :param filename: Name of the file containing graph data
        Opens the file (filename) and constructs a graph based on the data.
        :return: None, stores data in self.city_map
        """
        # Open the file and read lines
        with open(filename, 'r') as file:
            lines = file.readlines()
        # Parse lines and add edges to the graph
        for line in lines:
            # Split the line into tokens using '|', convert tokens to integers, and add edge to the graph
            start, end, distance = map(int, line.strip().split('|'))
            self.city_map.addEdge(start, end, distance)



    def isWithinServiceRange(self, restaurant: int, user: int, threshold: int) -> bool:
        """
        :param restaurant:
        the specific restaurant node you are looking from (start)
        :param user:
        the target user, the delivery customer (end)
        :param threshold:
        the max distance the customer can be from the restaurant 
        :return:
        true or false depending on if actual distance < threshold
        """
        self.dijkstra(restaurant, 0)
        if self.exists(user, 0) == False:
            return False
        if self.city_map.getVertex(user).getDistance() == sys.maxsize:
            return False
        if self.city_map.getVertex(user).getDistance() <= threshold:
            return True
        else:
            return False
    
    def dijkstra(self, start: int, tree: int):
        '''
        :param start:
        gives the root for the algorithm to build the tree
        :param tree:
        determines which variable to act upon 0 for city_map, 1 for MST
        '''
        if tree == 0:
            for v in self.city_map:
                v.setDistance(sys.maxsize)
                v.setPred(None)
        else:
            for v in self.MST:
                v.setDistance(sys.maxsize)
                v.setPred(None)
        pq = PriorityQueue()
        start_vertex = self.city_map.getVertex(start)
        start_vertex.setDistance(0)
        if tree == 0:
            pq.buildHeap([(v.getDistance(), v) for v in self.city_map])
        else:
            pq.buildHeap([(v.getDistance(), v) for v in self.MST])
        while not pq.isEmpty():
            current_vertex = pq.delMin()
            for next_vertex in current_vertex.getConnections():
                new_dist = current_vertex.getDistance() + current_vertex.getWeight(next_vertex)
                if new_dist < next_vertex.getDistance():
                    next_vertex.setDistance(new_dist)
                    next_vertex.setPred(current_vertex)
                    pq.decreaseKey(next_vertex, new_dist)
                    
    def exists(self, node: int, map: int):
        '''
        :param node:
        this is the node that the alg checks if exists
        :param map:
        this decides which map to use 0 for city_map, 1 for MST
        :return:
        returns true if node exists in map, false if it does not
        '''
        if map == 0:
            for i in self.city_map.vertList.values():
                if self.city_map.getVertex(node) == i:
                    return True
            return False
        else:
            for i in self.MAS.vertList.values():
                if self.MAST.getVertex(node) == i:
                    return True
            return False

    def buildMST(self, restaurant: int) -> bool:
        """
        :param restaurant: which node to make the MST root
        :return: nothing, just creates the MST
        """
        #make a visited list to prevent cycles

        self.prim(restaurant)   
        for v in self.city_map:
            self.MST.addVertex(v.id)
        for i in self.city_map:
            if i.getPred():
                self.MST.addEdge(i.id, i.getPred().id, i.getWeight(i.getPred()))
                self.MST.getVertex(i.id).setPred(self.MST.getVertex(i.getPred().id))
        
    def prim(self ,start):
        '''
        :param start: 
        which vertex the alg will use for the root
        :return:
        nothing, data is stored in the edge weights
        '''
        for v in self.city_map:
            v.setDistance(sys.maxsize)
            v.setPred(None)
        pq = PriorityQueue()
        start_vertex = self.city_map.getVertex(start)
        start_vertex.setDistance(0)
        pq.buildHeap([(v.getDistance(),v) for v in self.city_map])
        while not pq.isEmpty():
            current_vertex = pq.delMin()
            for next_vertex in current_vertex.getConnections():
                new_dist = current_vertex.getWeight(next_vertex)
                if next_vertex in pq and new_dist<next_vertex.getDistance():
                    next_vertex.setPred(current_vertex)
                    next_vertex.setDistance(new_dist)
                    pq.decreaseKey(next_vertex,new_dist)


    def minimalDeliveryTime(self, restaurant: int, user: int) -> int:
        """
        :param restaurant:
        the starting vertex
        :param user:
        the ending vertex
        :return:
        the shortest distance between the 2 vertexes
        """
        distance = 0
        self.buildMST(restaurant)
        while user != restaurant:
            print(user)
            distance += self.MST.getVertex(user).getWeight(self.MST.getVertex(user).getPred())
            user = self.MST.getVertex(user).getPred().id
        return distance

    
    def findDeliveryPath(self, restaurant: int, user: int) -> str:
        """
        :param restaurant:
        this is the starting vertex
        :param user:
        this is the end vertex
        :return:
        path followed by a bracket with the delivery time in it. Example of output "1->3->7->9 (24)" 
        where node 1 is the restaurant and 9 is the user's delivery address. 24 is the total time spent 
        if the delivery person were to follow the path 1->3->7->9.
        return 'INVALID' if the restaurant node or user node DNE
        """
        try:
            self.dijkstra(restaurant, 0)
            if self.exists(restaurant, 0) == False or self.exists(user, 0) == False:
                return 'INVALID'
            else:
                distance = f' ({self.city_map.getVertex(user).getDistance()})'
                address = user
                path = []
                path.append(address)
                while address != restaurant:
                    address = self.city_map.getVertex(address).getPred().id
                    path.append(address)
                path.reverse()
                delivPath = ''
                for i in path:
                    if delivPath == '':
                        delivPath = f'{i}'
                    else:
                        delivPath += f'-> {i}'
                return delivPath + distance
        except:
            return 'INVALID'

    def findDeliveryPathWithDelay(self, restaurant: int, user: int, delay_info: dict[int, int]) -> str:
        """
        :param restaurant:
        restaurant to start from
        :param user:
        target vertex that will find shortest distance too
        :param delay_info:
        update edges with this info
        :return:
        path followed by a bracket with the delivery time in it. Example of output "1->3->7->9 (24)" 
        where node 1 is the restaurant and 9 is the user's delivery address. 24 is the total time spent 
        if the delivery person were to follow the path 1->3->7->9.
        return 'INVALID' if the restaurant node or user node DNE
        """
        try:
            self.dijkstra(restaurant, 0)
        except:
            return 'INVALID'
        for v in list(delay_info):  
            self.city_map.addEdge(self.city_map.getVertex(v).getPred().id, v, self.city_map.getVertex(v).getPred().getWeight(self.city_map.getVertex(v)) + delay_info[v])
        return self.findDeliveryPath(restaurant, user)



    ## DO NOT MODIFY CODE BELOW!
    @staticmethod
    def nodeEdgeWeight(v):
        return sum([w for w in v.connectedTo.values()])

    @staticmethod
    def totalEdgeWeight(g):
        return sum([DeliveryService.nodeEdgeWeight(v) for v in g]) // 2

    @staticmethod
    def checkMST(g):
        for v in g:
            v.color = 'white'

        for v in g:
            if v.color == 'white' and not DeliveryService.DFS(g, v):
                return 'Your MST contains circles'
        return 'MST'

    @staticmethod
    def DFS(g, v):
        v.color = 'gray'
        for nextVertex in v.getConnections():
            if nextVertex.color == 'white':
                if not DeliveryService.DFS(g, nextVertex):
                    return False
            elif nextVertex.color == 'black':
                return False
        v.color = 'black'

        return True

# NO MORE TESTING CODE BELOW!
# TO TEST YOUR CODE, MODIFY test_delivery_service.py
