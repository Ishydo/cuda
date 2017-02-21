# cuda

OMP permet de faire du traitement parallèle très facilement, on peut typiquement transformer un comportement séquentiel for en comportement parallèle :
```cpp
for (int i = 1; i <= n; i++)
	{
	double xi = i*DX;
	sum += fpi(xi);
	}
return sum*DX;
```
devient 
```cpp
#pragma omp parallel for reduction(+:sum)
for (int i = 1; i <= n; i++)
	{
	double xi = i*DX;
	sum += fpi(xi);
	}
return sum*DX;
```

En une seule ligne le traitement devient parallèle et la réduction est faite automatiquement.
