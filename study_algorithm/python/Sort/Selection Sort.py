def selection_sort(arr):
    
    # For every slot in array
    for fillslot in range(len(arr)-1,0,-1):
        positionOfMax=0
        
        # For every set of 0 to fillslot+1
        for location in range(1,fillslot+1):
            # Set maximum's location
            if arr[location]>arr[positionOfMax]:
                positionOfMax = location

        temp = arr[fillslot]
        arr[fillslot] = arr[positionOfMax]
        arr[positionOfMax] = temp
		
		
		
arr = [3,5,2,7,6,8,12,40,21]
selection_sort(arr)
arr