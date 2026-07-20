CREATE TABLE shoes (
    shoe_id SERIAL PRIMARY KEY,
    shoe_brand_name VARCHAR(128) NOT NULL,
    shoe_brand_model VARCHAR(128) NOT NULL,
    shoe_brand_release_year INTEGER NOT NULL,
    UNIQUE(shoe_brand_name, shoe_brand_model, shoe_brand_release_year)
);

CREATE TABLE shoe_sole_imgs (
    shoe_sole_img_id SERIAL PRIMARY KEY,
    shoe_id INTEGER NOT NULL REFERENCES shoes(shoe_id),
    shoe_sole_img_path VARCHAR(256) NOT NULL
);

CREATE TABLE ml_shoe_sole_patterns (
    shoe_patterns SERIAL PRIMARY KEY,
    shoe_sole_img_id INTEGER NOT NULL REFERENCES shoe_sole_imgs(shoe_sole_img_id),
    shoe_sole_pattern VARCHAR(128) NOT NULL
);

INSERT INTO shoes(shoe_brand_name, shoe_brand_model, shoe_brand_release_year) 
VALUES 
('Nike', 'Airmax', 2012),
('Nike', 'Air-Force-1', 2013),
('Adidas', 'UltraBoost', 2021),
('Puma', 'Palermo', 2014);

INSERT INTO shoe_sole_imgs(shoe_id, shoe_sole_img_path)
VALUES
('1', '../imgs/Nike-Airmax-2012'),
('2', '../imgs/Nike-Air-Force-1-2013'),
('3', '../imgs/Adidas-Ultraboost-2021'),
('4', '../imgs/Puma-Palermo-2014');

INSERT INTO ml_shoe_sole_patterns(shoe_sole_img_id, shoe_sole_pattern)
VALUES
('1', 'circles'),
('1', 'stripes'),
('2', 'wavy'),
('2', 'circles'),
('2', 'zigzag'),
('3', 'stripes'),
('4', 'zigzag'),
('4', 'wavy');