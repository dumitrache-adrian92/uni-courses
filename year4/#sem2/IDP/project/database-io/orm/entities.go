package db

type Artist struct {
	ID     uint    `gorm:"primaryKey"`
	Name   string  `gorm:"unique"`
	Albums []Album `gorm:"constraint:OnUpdate:CASCADE"`
	Songs  []Song  `gorm:"constraint:OnUpdate:CASCADE"`
}

type Album struct {
	ID       uint   `gorm:"primaryKey"`
	Name     string `gorm:"unique"`
	ArtistID uint
	Artist   Artist
	Songs    []Song `gorm:"constraint:OnUpdate:CASCADE"`
}

type Song struct {
	ID       uint `gorm:"primaryKey"`
	Name     string
	ArtistID uint
	AlbumID  *uint
	Artist   Artist         `gorm:"constraint:OnUpdate:CASCADE"`
	Album    Album          `gorm:"constraint:OnUpdate:CASCADE"`
	Feedback []UserFeedback `gorm:"constraint:OnUpdate:CASCADE"`
}

type UserFeedback struct {
	ID      uint   `gorm:"primaryKey"`
	User    string `gorm:"index"`
	Score   int
	Comment string

	SongID uint
}
