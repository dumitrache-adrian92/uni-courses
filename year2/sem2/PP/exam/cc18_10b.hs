data CircularList a = CL {getPos :: Int,
                            getList :: [a]}
    deriving (Show, Eq)

createCL list = CL (length list - 1) list

get (CL pos list) = head $ drop pos list

prev (CL pos list) =
    let
        new_pos = pos - 1
    in
        if new_pos == 0 then CL (length list - 1) list else CL new_pos list