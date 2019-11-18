from collections import deque

def steps_mhanoy(tower):
    l = len(tower)
    rangel = range(l)   # it'll help optimisation, the solution
                        # fails time to time
    steps = 0
    state = 0   # state is binary of  |discN|discN-1|...|disc2|disc1|
                # where each discK = rod on which that disc is located
    win = 0     # win is state where each discK == 00b

    def move(rod, disc):
        nonlocal state
        disc *= 2            # each disc is represented as 2 bits
        state &= ~(3<<disc)  # 3 = all rods -> remove all rods for that disc
        state |= rod<<disc   # write down rod
    
    def get_rod_top(rod):
        st = state
        for i in rangel:
            r = 3&st        # get topmost disc rod
            if r == rod:    
                return i
            st >>= 2        # move to the next disc
        return l            # we can return anything, but l is better because we get
                            # less comparison later

    for i in rangel:        # fill in the state
        move(tower[i] - 1, i)
    
    if state == win:        # bfs won't work if we are already in a right state
        return 0

    # to solve the case, we will use breadth-first search
    bfs = deque()       # the list of unexplored states
    bfs.append(state)   # root state atop
    depth = dict()      # depth measure
    depth[state] = 0    # depth of starting state is 0
    range4 = range(4)   # just a bit of optimisation will help
    while True:
        cstate = state = bfs.popleft()  # get the next unexplored state
        steps = depth[state]            # get it's depth
        
        # get all the tops of the rods to move them
        d = [get_rod_top(r) for r in range4]
        for fro in range4:    # try to move from every rod
            if d[fro] == l:     # if rod is empty, skip
                continue
            for to in range4: # iterate over every other rod to put onto
                if d[to] > d[fro]:  # if the disc is bigger on the rod or rod is empty
                    state = cstate  # restore state to state of exploration
                    move(to, d[fro])# move the rod
                    if state == win:# if achieved finish state, return immediately
                        return steps + 1
                                    # if state hadn't been found yet
                    if state not in depth:
                                    # set state depth
                        depth[state] = steps + 1
                                    # add into exploration queue
                        bfs.append(state)
    return depth[0]

def main():
	n = int(input())
	s = input()
	s = s.split(' ')
	tower = [int(x) for x in s]
	
	steps = steps_mhanoy(tower)
	
	print ("Steps = {steps}".format (steps = steps))
    
if __name__ == "__main__":
	main()
