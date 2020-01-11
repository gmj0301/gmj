#include<stdio.h>
int sudo[9][9];
int snh[9], snl[9], sng[9];
int temp = 0, judge_all = 0;

void shezhi(int i, int j){
	snh[i]--;
	snl[j]--;
	int k = (i / 3) * 3 + (j / 3);
	sng[k]--;
}

void output(){
	for(int i = 0; i < 9; i++){
		printf("%d", sudo[i][0]);
		for(int j = 1; j < 9; j++)
	        printf(" %d", sudo[i][j]);
	    printf("\n");
	}   
}

bool judge(int h, int l){
	for(int i = 0; i < 9; i++)
	    if(sudo[i][l] == sudo[h][l] && i != h)
	        return false;
	for(int i = 0; i < 9; i++)
	    if(sudo[h][l] == sudo[h][i] && i != l)
	        return false;
	int x = (h / 3) * 3;
	int y = (l / 3) * 3;
	for(int i = x; i < x+3; i++)
	    for(int j = y; j < y+3; j++)
	        if(sudo[h][l] == sudo[i][j] && i != h && j != l)
	            return false;
	return true;
}

void solve_sudo(int i, int j){
	if(judge_all == 1) return;
    
    int k, h, l, temp = 0;
    for(k = sudo[i][j] + 1; k <= 9; k++){
		sudo[i][j] = k;
		if(judge(i, j)){
		
			h = i; l = j + 1;
			for( ; h < 9; h++){
				for( ; l < 9; l++)
				    if(sudo[h][l] == 0){
				    	temp = 1;
				    	break;
					}
				if(temp == 1) break;
			    else l = 0;
			}
			if(temp == 1) solve_sudo(h, l);
			else{
				judge_all = 1;
			    return;
			} 
			if(judge_all == 1) return;
		}
		
	}
	sudo[i][j] = 0;
	return;	
}



void s(){
	while(1)
	{
		
		int num = 0, w, s;
		for(int i = 0; i < 9; i++)
			for(int j = 0; j < 9; j++){
				scanf("%d", &sudo[i][j]);
				if(num == 0 && sudo[i][j] == 0)
				{
					w = i;
					s = j;
					num ++ ;
				}
			}
		
		solve_sudo(w, s);
		output();	
	}
	return 0;
} 
