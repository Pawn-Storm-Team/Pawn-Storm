//John Bedette 2021
//Chess piece data structure
//======================
//@TODO:
// 1. adjust for second player
// 2. test mutability and usability, rust gets weird with throwing things away
// 3. start defining legal move options 
// 4. profit

//storing piece type in an enum
//lets us use match on piece type for a future legal_move()
#[derive(Debug,Clone)]
pub enum Kind {
    PAWN,
    ROOK,
    KNIGHT,
    BISHOP,
    QUEEN,
    KING
}

//piece struct, stores x,y and id
//id will be used for lookup and board position
#[derive(Debug,Clone)]
pub struct Piece {
    pub p:Kind,
    pub id:u8,
    pub x:u8,
    pub y:u8,
}

//constructor for piece
impl Piece {
    pub fn new(p:Kind,id:u8, x:u8,y:u8) -> Self{
        Self{
            p,
            id,
            x,
            y
        }
    }
}

//legal move will return a bool if move is legal, 
//@todo: make pieces into enum variants so we can just match on that and possibly not have an enum val in the piece struct
fn legal_move(piece:Piece)->bool{

    //@todo: remove, display fixing during testing
    println!();

    let mut legal:bool = false;
    //do stuff
    // + check if inbounds
    // + check if piece
    //      - check if piece is friendly
    //now do piece specific stuff
    match piece.p.clone(){
        Kind::PAWN =>{
            println!("legal move check {:?}",piece.p.clone());
        },    
        Kind::ROOK =>{
            println!("legal move check {:?}",piece.p.clone());

        },    
        Kind::KNIGHT =>{
            println!("legal move check {:?}",piece.p.clone());

        },    
        Kind::BISHOP =>{
            println!("legal move check {:?}",piece.p.clone());

        },    
        Kind::QUEEN =>{
            println!("legal move check {:?}",piece.p.clone());

        },
        Kind::KING =>{
            println!("legal move check {:?}",piece.p.clone());

        },
        _=>{println!{"Piece type is undefined."}},
    }
    legal = true;
    return legal
}


//@TODO: put this into a testing file
//testing function, proof of things building and working
pub fn test_build(){
    
    //storage of piece structs,
    //@TODO:this would probably be good as its own struct
    let mut player1= <Vec<Piece>>::new();
    let mut board= 
    
    //@TODO: doing 1 to 17 because chess notation starts with 1, might change later
    for i in 1..17{
        //@TODO:proper error handling -> _p because if there is an error we don't use _p
        let mut _p:Piece;

        //match on i for build
        //@TODO: adjust for other other set of pieces
        match i{
            1..=8 => {
                _p = Piece::new(Kind::PAWN,i,i,1);
                player1.push(_p);
            },
            9|16 => {
                _p = Piece::new(Kind::ROOK,i,i-8,0);
                player1.push(_p);
            },
            10|15 => {
                _p = Piece::new(Kind::KNIGHT,i,i-8,0);
                player1.push(_p);
            },
            11|14 => {
                _p = Piece::new(Kind::BISHOP,i,i-8,0);
                player1.push(_p);

            },
            12 => {
                _p = Piece::new(Kind::QUEEN,i,i-8,0);
                player1.push(_p);

            },
            13 =>{
                _p = Piece::new(Kind::KING,i,i-8,0);
                player1.push(_p);

            }
            _=>println!("Too high or low")
        }
    }

    //demo and display info
    println!("{:?}\n\n",player1);
    for i in 0..8{
        print!("{:?}\t",player1[i].p)
    }
    println!();
    for i in 8..16{
        print!("{:?}\t",player1[i].p)
    }
    println!("\nDoing something with the bool returned from legal_move: {}\n",legal_move(player1[1].clone()));
    //display board
    println!("\t   A     B     C     D     E     F     G     H");
    for i in 8..1{ //start with rank, traversing down 
        print!("\t   -     -     -     -     -     -     -     -");
        print!("{}\t", i);//display rank on left of board
        for k in 1..8{
            if(player1[board[k][i].copy()].id != 0)

        }

    }
}
