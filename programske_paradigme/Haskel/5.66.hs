listaUPar :: [(String, String)] -> ([String], [String])
listaUPar lista = (map fst lista, map snd lista) 

listaUPar' :: [(String, String)] -> ([String], [String])
listaUPar' = unzip