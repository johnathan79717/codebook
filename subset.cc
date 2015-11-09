int sub = sup;
do {
  // process on subsets
  sub = (sub - 1) & sup;
} while(sub != sup);