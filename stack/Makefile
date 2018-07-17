cc = gcc
target1 = ls
source1 = lstack_test.c lstack.c

target2 = ss
source2 = sqstack_test.c sqstack.c

$(target1):$(source1)
	$(cc) -o $(target1) $(source1)

$(target2):$(source2)
	$(cc) -o $(target2) $(source2)

clean:
	rm -rf $(target1) $(target2)
