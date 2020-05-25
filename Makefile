objects = src/main.o src/helpfulFunctions.o src/menuFunctions.o src/handler.o

diseaseAggregator : $(objects)
		cc -o diseaseAggregator $(objects)
		@echo "========================================================================"
		@echo "|Try running: ./diseaseAggregator -w 70 -b 10 -i 10                    |"
		@echo "|Validation: ./validator.sh bin/small.txt 10 10 70                     |"
		@echo "========================================================================"

src/main.o : include/Interface.h
src/helpfulFunctions.o : include/Interface.h
src/menuFunctions.o : include/Interface.h
src/handler.o : include/Interface.h
# src/recordList.o : include/Interface.h
# src/hashTable.o : include/Interface.h
# src/avlTree.o : include/Interface.h
# src/freeFunct.o : include/Interface.h
# src/uniqueList.o : include/Interface.h

.PHONY: clean
clean :
		@echo "Cleaning ..."
		rm diseaseAggregator $(objects)
