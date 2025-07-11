data CircularList a = CL {getPos :: Int,
                            getList :: [a]}
    deriving (Show, Eq)

createCL list = CL 0 list

get (CL pos list) = head $ drop pos list

next (CL pos list) =
    let
        new_pos = pos + 1
    in
        if new_pos == length list then CL 0 list else CL new_pos list