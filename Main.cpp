// Main.cpp

int main(){
  bool run = true;
  char input [1000];
  Node* tree = new Node;
  while(run == true){
    cout<<"Add numbers (A)"<<endl
    <<"Add file (F)"<<endl<<"Show tree(S)"<<endl<<"Quit(Q)"<<endl;
    cin>>input;
    if(input[0] == 'A'){
      cout<<"Enter your number(s) separated by spaces"<<endl;
      cin>>input;
      makeBinary(input);
    }
    else if(input[0] == 'F'){
      cout<<"Enter the name of your file"<<endl;
      cin>>input;
      fstream myFile(input);
      while(myFile >> .......){
        makeBinary(uuuuuuhhhhh);
      }
    }
    else if(input[0] == 'S'){
      // print the heap
      // add tabs bsaed on the depth of each node
    }
    else if(input[0] == 'Q'){
      run = false;
    }
    else{
      cout<<input[0]<<" is not a valid command"<<endl;
    }
  } 
  return 0;
}
